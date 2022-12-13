using HandyControl.Controls;
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
    /// Логика взаимодействия для ScriptView.xaml
    /// </summary>
    public partial class ScriptView : UserControl
    {
        public ScriptView()
        {
            InitializeComponent();
        }

        private void OnScriptSelectionChange(object sender, EventArgs e)
        {
            var script = this.DataContext as ECS.Script;
            var cb = sender as System.Windows.Controls.ComboBox;
            if (cb.SelectedItem == null)
            {
                if (Array.Exists(Project.Project.Current.AvailableScripts, x => x == script.ScriptName))
                {
                    cb.SelectedItem = script.ScriptName;
                }
                else
                {
                    /* TODO warn that script no longer available*/ 
                    script.ScriptName = null;
                }
            }
            else
            {
                script.ScriptName = cb.SelectedItem.ToString();
            }
        }
    }
}
