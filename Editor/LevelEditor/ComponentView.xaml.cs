﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Editor.LevelEditor
{
    /// <summary>
    /// Логика взаимодействия для ComponentView.xaml
    /// </summary>
    [ContentProperty("ComponentContent")]
    public partial class ComponentView : UserControl
    {
        public string Header
        {
            get { return (string)GetValue(HeaderProperty); }
            set { SetValue(HeaderProperty, value); }
        }

        public static readonly DependencyProperty HeaderProperty = DependencyProperty.Register(nameof(Header), typeof(string), typeof(ComponentView));

        public Uri ComponentIcon
        {
            get { return (Uri)GetValue(ComponentIconProperty); }
            set { SetValue(ComponentIconProperty, value); }
        }

        public static readonly DependencyProperty ComponentIconProperty = DependencyProperty.Register(nameof(ComponentIcon), typeof(Uri), typeof(ComponentView));

        public FrameworkElement ComponentContent
        {
            get { return (FrameworkElement)GetValue(ComponentContentProperty); }
            set { SetValue(ComponentContentProperty, value); }
        }
        public static readonly DependencyProperty ComponentContentProperty = DependencyProperty.Register(nameof(ComponentContent), typeof(FrameworkElement), typeof(ComponentView));

        public ComponentView()
        {
            InitializeComponent();
        }
    }
}
