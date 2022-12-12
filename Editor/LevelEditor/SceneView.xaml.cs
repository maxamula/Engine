using CLIEngine;
using Editor.ECS;
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

namespace Editor.LevelEditor
{
    /// <summary>
    /// Логика взаимодействия для SceneView.xaml
    /// </summary>
    public partial class SceneView : UserControl
    {
        public SceneView()
        {
            InitializeComponent();
        }

        private void OnObjectSelectionChanged(object sender, EventArgs e)
        {
            var obj = (sender as TreeView).SelectedItem;
            ComponentsView.Instance.DataContext = obj;
        }

        private void OnAddChildClick(object sender, RoutedEventArgs e)
        {
            object item = tree.SelectedItem;
            if (item is Project.Scene)
                (item as Project.Scene).AddChild("GameObj");
            else if (item is ECS.GameObject)
                (item as ECS.GameObject).AddChild("GameObject");
        }

        private void OnRemoveChildClick(object sender, RoutedEventArgs e)
        {
            object item = tree.SelectedItem;
            if(item is ECS.GameObject)
            {
                var obj = (ECS.GameObject)item;
                if (obj.Parent == null)
                    obj.ParentScene.RemoveChild(obj);
                else
                    obj.Parent.RemoveChild(obj);
            }
        }

    }
}
