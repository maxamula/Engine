using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace Editor.ECS
{
    /// <summary>
    /// Game object sript component
    /// </summary>
    [DataContract]
    public class Script : Component
    {
        public Script(GameObject parent) : base(parent)
        {

        }
        [DataMember]
        public string ScriptName
        {
            get => _scriptName;
            set
            {
                if(_scriptName != value)
                {
                    _scriptName = value;
                    OnPropertyChanged(nameof(ScriptName));
                }
            }
        }
        private string _scriptName = "";
    }
}
