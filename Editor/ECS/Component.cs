using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace Editor.ECS
{

    [DataContract]
    public abstract class Component : VMBase
    {
        public Component(GameObject parent)
        {
            Object = parent;
        }
        [DataMember]
        public GameObject Object
        {
            get => _object;
            set
            {
                if(_object != value ) 
                {
                    _object = value;
                    OnPropertyChanged(nameof(Object));
                }
            }
        }
        private GameObject _object;
    }
}
