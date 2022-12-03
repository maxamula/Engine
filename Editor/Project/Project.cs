using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Intrinsics.Arm;
using System.Runtime.Serialization;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Xml.Linq;

namespace Editor.Project
{
    [DataContract(Name = "Proj")]
    public class Project : VMBase
    {
        // Public
        public Project()
        {

        }

        //Properties
        [DataMember]
        public string Name { get; /* TODO private*/ set; }
        [DataMember]
        public string Path { get; /* TODO private*/ set; }
        public ReadOnlyObservableCollection<Scene> Scenes { get; private set; }
        public string FullPath { get => $@"{Path}{Name}\{Name}.ahh"; }
        public static Project Current { get => Application.Current.MainWindow.DataContext as Project; }

        private bool _isBuildAvailable = false;
        public bool IsBuildAvailable
        {
            get => _isBuildAvailable;
            set
            {
                if (_isBuildAvailable != value)
                {
                    _isBuildAvailable = value;
                    OnPropertyChanged(nameof(IsBuildAvailable));
                }
            }
        }
        private string[] _availableScripts;
        public string[] AvailableScripts
        {
            get => _availableScripts;
            set
            {
                if (_availableScripts != value)
                {
                    _availableScripts = value;
                    OnPropertyChanged(nameof(AvailableScripts));
                }
            }
        }
        public void AddScene(string sceneName)
        {
            Debug.Assert(!string.IsNullOrEmpty(sceneName.Trim()));
            _scenes.Add(new Scene(sceneName));
        }
        public void RemoveScene(Scene scene)
        {
            Debug.Assert(_scenes.Contains(scene));
            
        }
        public void Unload()
        {
            // TODO unload visual studio solution
        }
        public static Project Load(string file)
        {
            Debug.Assert(File.Exists(file));
            return Utils.Serializer.Deserialize<Project>(file);
        }

        public static void Save(Project project)
        {
            Debug.Assert(project != null);
            Utils.Serializer.Serialize<Project>(project, project.FullPath);
        }

        //Private
        [OnDeserialized]
        private void OnDesirialized(StreamingContext context)
        {
            if (_scenes != null)
            {
                Scenes = new ReadOnlyObservableCollection<Scene>(_scenes);
                OnPropertyChanged(nameof(Scenes));  // update ui
            }
        }

        [DataMember(Name = "Scenes")]
        ObservableCollection<Scene> _scenes = new ObservableCollection<Scene>();
    }
}
