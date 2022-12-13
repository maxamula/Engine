using Editor.Project;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Editor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : HandyControl.Controls.Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Loaded += OnMainWindowLoaded;
            Closed += OnMainWindowClosed;
            ShowProjectDialog();
        }

        private void OnMainWindowClosed(object? sender, EventArgs e)
        {
            (this.DataContext as Project.Project)?.Unload();
        }

        private void OnMainWindowLoaded(object sender, RoutedEventArgs e)
        {
            Loaded -= OnMainWindowLoaded;
        }

        async private void ShowProjectDialog()
        {
            var projectDialog = new ProjectDialog();
            if (projectDialog.ShowDialog() == false || projectDialog.DataContext == null)
                Application.Current.Shutdown();         // Shutdown application if user clicked exit btn or error 
            else
            {
                Project.Project.Current?.Unload();          // unload old proj
                DataContext = projectDialog.DataContext;    // set proj as datacontext

                var project = DataContext as Project.Project;
                await Task.Run(() =>
                {
                    Utils.SolutionManager.Build(project, project.GetConfigName(true), new Action(() =>
                    {
                        // TODO After Building solution load scripts components

                    }));
                });

            }
        }

        private void OnSaveClick(object sender, EventArgs e)
        {
            Project.Project.Save(Project.Project.Current);
        }
    }
}
