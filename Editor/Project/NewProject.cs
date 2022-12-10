using Editor.Utils;
using Microsoft.VisualBasic.FileIO;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Editor.Project
{
    [DataContract]
    public class ProjectTemplate
    {
        [DataMember]
        public string ProjectType { get; set; }
        [DataMember]
        public string ProjectFile { get; set; }
        [DataMember]
        public List<string> Folders { get; set; }
        public byte[] Icon { get; set; }
        public byte[] Screenshot { get; set; }
        public string ProjectFilePath { get; set; }
        public string IconFilePath { get; set; }
        public string ScreenshotFilePath { get; set; }
        public string TemplatePath { get; set; }
    }

    class NewProject : VMBase
    {
        // Constructor
        public NewProject()
        {
            ProjectTemplates = new ReadOnlyObservableCollection<ProjectTemplate>(_projectTemplates);
            try
            {
                var templateFiles = Directory.GetFiles(_templatePath, "template.xml", System.IO.SearchOption.AllDirectories);
                Debug.Assert(templateFiles.Any());
                foreach (var file in templateFiles)
                {
                    var template = Utils.Serializer.Deserialize<ProjectTemplate>(file);
                    template.IconFilePath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(file), "Icon.png"));
                    template.Icon = File.ReadAllBytes(template.IconFilePath);
                    template.ScreenshotFilePath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(file), "Screenshot.png"));
                    template.Screenshot = File.ReadAllBytes(template.ScreenshotFilePath);
                    template.ProjectFilePath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(file), "project.ahh"));
                    template.TemplatePath = Path.GetDirectoryName(file);
                    _projectTemplates.Add(template);
                    ValidatePath(); // Validate default path
                }
            }
            catch (Exception ex)
            {

            }
        }
        // Public
        // Methods
        public string CreateProject(ProjectTemplate template)
        // Returns path to a newly created project file
        {
            if (!ValidatePath())
                return string.Empty;
            if (template == null)
                return string.Empty;
            if (!Path.EndsInDirectorySeparator(ProjectPath))   // Append separator if path does not end with it
                ProjectPath += @"\";
            var path = $@"{ProjectPath}{ProjectName}\";
            try
            {
                if (!Directory.Exists(path))
                    Directory.CreateDirectory(path);
                // Create folders for game parts
                foreach (var folder in template.Folders)
                {
                    Directory.CreateDirectory(Path.GetFullPath(Path.Combine(Path.GetDirectoryName(path), folder)));
                }
                var dirInfo = new DirectoryInfo(path + @".engine\");
                dirInfo.Attributes |= FileAttributes.Hidden;
                // Copy template files to a project path
                File.Copy(template.IconFilePath, Path.GetFullPath(Path.Combine(dirInfo.FullName, "Icon.png")));
                File.Copy(template.ScreenshotFilePath, Path.GetFullPath(Path.Combine(dirInfo.FullName, "Screenshot.png")));

                var projectXml = File.ReadAllText(template.ProjectFilePath);
                projectXml = string.Format(projectXml, ProjectName, ProjectPath);
                var projectPath = Path.GetFullPath(Path.Combine(path, $"{ProjectName}.ahh"));
                File.WriteAllText(projectPath, projectXml);

                var solution = File.ReadAllText(Path.Combine(template.TemplatePath, "MSVCSolution"));
                solution = string.Format(solution, ProjectName, "{" + Guid.NewGuid().ToString().ToUpper() + "}", "{" + Guid.NewGuid().ToString().ToUpper() + "}");
                File.WriteAllText(Path.GetFullPath(Path.Combine(path, $"{ProjectName}.sln")), solution);

                // create vissual studio solution here
                var project = File.ReadAllText(Path.Combine(template.TemplatePath, "MSVCProject"));
                project = string.Format(project, ProjectName, "{" + Guid.NewGuid().ToString().ToUpper() + "}");
                File.WriteAllText(Path.GetFullPath(Path.Combine(path, $"GameCode\\{ProjectName}.vcxproj")), project);
                // Create folders for engine binaries/includes
                Directory.CreateDirectory(Path.Combine(path, $"GameCode\\Engine"));
                Directory.CreateDirectory(Path.Combine(path, $"GameCode\\Engine\\API"));
                FileSystem.CopyDirectory("Engine", Path.Combine(path, $"GameCode\\Engine"));
                var initializer = File.ReadAllText(Path.Combine(template.TemplatePath, "Init"));
                initializer = string.Format(initializer, ProjectName);
                File.WriteAllText(Path.GetFullPath(Path.Combine(path, $"GameCode\\{ProjectName}.cpp")), initializer);
                string[] files = { Path.GetFullPath(Path.Combine(path, $"GameCode\\{ProjectName}.cpp")) };
                SolutionManager.AddFiles(Path.GetFullPath(Path.Combine(path, $"{ProjectName}.sln")), ProjectName, files);
                return path;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                return string.Empty;
            }

        }
        // Properties
        public bool IsValid
        {
            get => _isValid;
            set
            {
                if (_isValid != value)
                {
                    _isValid = value;
                    OnPropertyChanged(nameof(IsValid));
                }
            }
        }
        public string ErrorMsg
        {
            get => _errorMsg;
            set
            {
                if (_errorMsg != value)
                {
                    _errorMsg = value;
                    OnPropertyChanged(nameof(ErrorMsg));
                }
            }
        }
        public ReadOnlyObservableCollection<ProjectTemplate> ProjectTemplates { get; }
        public string ProjectName
        {
            get => _projectName;
            set
            {
                if (_projectName != value)
                {
                    _projectName = value;
                    ValidatePath();
                    OnPropertyChanged(nameof(ProjectName));
                }
            }
        }
        public string ProjectPath
        {
            get => _projectPath;
            set
            {
                if (_projectPath != value)
                {
                    _projectPath = value;
                    ValidatePath();
                    OnPropertyChanged(nameof(ProjectPath));
                }
            }
        }
        // Private
        // Methods
        private bool ValidatePath()
        {
            var path = ProjectPath;
            if (!Path.EndsInDirectorySeparator(path))   // Append separator if path does not end with it
                path += @"\";
            path += $@"{ProjectName}\";
            IsValid = false;
            if (string.IsNullOrEmpty(ProjectName.Trim()))
            {
                ErrorMsg = "Invalid project name.";
            }
            else if (ProjectName.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
            {
                ErrorMsg = "Invalid chars are used in project name.";
            }
            else if (string.IsNullOrEmpty(ProjectPath.Trim()))
            {
                ErrorMsg = "Invalid project path.";
            }
            else if (ProjectPath.IndexOfAny(Path.GetInvalidPathChars()) != -1)
            {
                ErrorMsg = "Invalid chars are used in project name.";
            }
            else if (Directory.Exists(path) && Directory.EnumerateFileSystemEntries(path).Any())
            {
                ErrorMsg = "Selected folder is not empty.";
            }
            else
            {
                ErrorMsg = string.Empty;
                IsValid = true;
            }
            return IsValid;
        }
        // Fields
        private bool _isValid = true;
        private string _errorMsg = string.Empty;
        private string _projectName = "New_Project";                                                                                                  // Project name
        private string _projectPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\Engine\";                                 // Project path
        private readonly string _templatePath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + @"\Engine\EngineTemplates\";
        private ObservableCollection<ProjectTemplate> _projectTemplates = new ObservableCollection<ProjectTemplate>();
    }
}
