using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Markup;

namespace Editor.ECS
{
    [DataContract]
    abstract public class GOParent : VMBase
    {
        abstract public GameObject AddChild(string name);
        abstract public void RemoveChild(GameObject obj);
    }
}
