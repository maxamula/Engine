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
    /// Логика взаимодействия для ComponentsView.xaml
    /// </summary>
    public partial class ComponentsView : UserControl
    {
        public static ComponentsView Instance { get; private set; }
        public ComponentsView()
        {
            InitializeComponent();
            DataContext = null;
            Instance = this;
        }
    }
}
