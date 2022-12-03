using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace Editor.ECS
{
    [DataContract]
    public class GameObject : VMBase
    {
        public GameObject()
        {
            Components = new ReadOnlyObservableCollection<Component>(_components);
        }
        public ReadOnlyObservableCollection<Component> Components; 


        [DataMember]
        private ObservableCollection<Component> _components = new ObservableCollection<Component>();
    }
}
