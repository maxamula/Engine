
using Editor.Project;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Markup;

namespace Editor.ECS
{
    [DataContract]
    [KnownType(typeof(Script))]
    public class GameObject : GOParent
    {
        public GameObject(string name)
        {
            Name = name;
            Components = new ReadOnlyObservableCollection<Component>(_components);
            Children = new ReadOnlyObservableCollection<GameObject>(_children);
        }
        public override GameObject AddChild(string name)
        {
            ECS.GameObject obj = new ECS.GameObject(name);
            obj.Parent = this;
            obj.ParentScene = ParentScene;
            obj._GameObject = _GameObject.AddChild();
            _children.Add(obj);
            return obj;
        }
        public override void RemoveChild(GameObject obj)
        {
            Debug.Assert(obj != this);
            _children.Remove(obj);
            _GameObject.RemoveChild(obj._GameObject);
        }
        public void AddChildrenRecursive()
        {
            foreach(var child in _children)
            {
                child._GameObject = _GameObject.AddChild();
                child.AddChildrenRecursive();
            }
        }
        public CLIEngine.GameObject _GameObject;
        public ReadOnlyObservableCollection<Component> Components { get; private set; } 
        public ReadOnlyObservableCollection<GameObject> Children { get; private set; }
        [DataMember]
        public GameObject Parent { get; private set; }
        [DataMember]
        public Scene ParentScene { get; set; }
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
        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            Components = new ReadOnlyObservableCollection<Component>(_components);
            Children = new ReadOnlyObservableCollection<GameObject>(_children);
            _components.Add(new Script(this));
        }
        [DataMember]
        private ObservableCollection<Component> _components = new ObservableCollection<Component>();
        [DataMember]
        private ObservableCollection<GameObject> _children = new ObservableCollection<GameObject>();
        private string _name = "Game_object";
    }
}
