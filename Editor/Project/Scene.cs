﻿using CLIEngine;
using HandyControl.Tools.Extension;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Project
{
    [DataContract]
    public class Scene : ECS.GOParent
    {
        public Scene(string name)
        {
            Name = name;
            _Scene = CLIEngine.Core.CreateScene();
            GameObjects = new ReadOnlyObservableCollection<ECS.GameObject>(_gameObjects);
        }
        public override ECS.GameObject AddChild(string name)
        {
            ECS.GameObject obj = new ECS.GameObject(name);
            obj._GameObject = _Scene.AddChild();
            obj.ParentScene = this;
            _gameObjects.Add(obj);
            return obj;
        }
        public override void RemoveChild(ECS.GameObject obj)
        {
            Debug.Assert(_gameObjects.Contains(obj));
            _gameObjects.Remove(obj);
            _Scene.RemoveChild(obj._GameObject);
        }
        [DataMember]
        public string Name 
        {
            get => _name;
            set
            {
                if(_name != value)
                {
                    _name = value;
                    OnPropertyChanged(nameof(Name));
                }
            }
        }
        public CLIEngine.Scene _Scene { get; private set; }
        public ReadOnlyObservableCollection<ECS.GameObject> GameObjects { get; private set; }
        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            _Scene = CLIEngine.Core.CreateScene();
            GameObjects = new ReadOnlyObservableCollection<ECS.GameObject>(_gameObjects);
        }
        private string _name;
        [DataMember]
        private ObservableCollection<ECS.GameObject> _gameObjects = new ObservableCollection<ECS.GameObject>();
    }
}
