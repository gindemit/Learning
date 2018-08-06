using System;
using UnityEditor;
using UnityEngine;
using UnityEngine.Experimental.UIElements;
using UnityEditor.Experimental.UIElements;
using UnityEditor.Experimental.UIElements.GraphView;

namespace UIElementsExamples
{
    public class WorkSpace : GraphView
    {
        private readonly RectangleSelector m_Selector = new RectangleSelector();
        private readonly SelectionDragger m_SelectionDragger = new SelectionDragger();
        public WorkSpace()
        {
            AddToClassList("workSpaceClass");
            SetupZoom(0.1f, 2f, 0.15f, 1f);
            
            this.AddManipulator(m_SelectionDragger);
            this.AddManipulator(m_Selector);
        }

    }

    public class PortDataOne { }
    public class PortDataTwo { }
    public class PortDataThree { }

    public class DraggableBox : Node
    {
        public DraggableBox()
        {
            SetSize(new Vector2(300, 300));
            capabilities =
                Capabilities.Selectable |
                Capabilities.Collapsible |
                Capabilities.Resizable |
                Capabilities.Movable |
                Capabilities.Deletable |
                Capabilities.Droppable |
                Capabilities.Ascendable;

            title = "Floating Box";
            AddToClassList("draggableBoxClass");

            AddPorts(typeof(PortDataOne));
            AddPorts(typeof(PortDataTwo));
            AddPorts(typeof(PortDataThree));
        }

        private void AddPorts(Type type)
        {
            inputContainer.Add(InstantiatePort(Orientation.Horizontal, Direction.Input, Port.Capacity.Multi, type));
            outputContainer.Add(InstantiatePort(Orientation.Horizontal, Direction.Output, Port.Capacity.Multi, type));
        }
    }



#if UNITY_2018
    public class E08_EditorControls : EditorWindow
    {
        [MenuItem("UIElementsExamples/08_Nodes")]
        public static void ShowExample()
        {
            var window = GetWindow<E08_EditorControls>();
            window.minSize = new Vector2(300, 300);
            window.titleContent = new GUIContent("Example 8");
        }

        private VisualElement m_Root;
        public void OnEnable()
        {
            m_Root = this.GetRootVisualContainer();
            m_Root.AddStyleSheetPath("mystyles");
            m_Root.AddToClassList("rootClass");

            WorkSpace ws = new WorkSpace();
            m_Root.Add(ws);

            const int itemsCount = 5;
            for (int i = 0; i < itemsCount; i++)
            {
                DraggableBox db = new DraggableBox();
                db.transform.position = new Vector3(i * (db.layout.width + 20), 0);
                ws.AddElement(db);
            }

            /*Texture2D backgroundTexrure = AssetDatabase.LoadAssetAtPath<Texture2D>("Assets/Textures/background.png");
            var image = new Image()
            {
                image = new UnityEngine.Experimental.UIElements.StyleSheets.StyleValue<Texture>(backgroundTexrure),
                sourceRect = new Rect(0, 0, 50, 50)
            };
            boxes.Add(image);*/
        }
    }
#endif
}
