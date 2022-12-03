using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Project
{
    [DataContract]
    public class Scene : VMBase
    {
        public Scene(string name)
        {
            Name = name;
            _scene = CLIEngine.Core.CreateScene();
            GameObjects = new ReadOnlyObservableCollection<ECS.GameObject>(_gameObjects);
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
        public ReadOnlyObservableCollection<ECS.GameObject> GameObjects;
        [OnDeserialized]
        private void OnDeserialized(StreamingContext context)
        {
            _scene = CLIEngine.Core.CreateScene();
            GameObjects = new ReadOnlyObservableCollection<ECS.GameObject>(_gameObjects);
        }

        private string _name;
        [DataMember]
        private ObservableCollection<ECS.GameObject> _gameObjects = new ObservableCollection<ECS.GameObject>();
        private CLIEngine.Scene _scene;
    }
}
