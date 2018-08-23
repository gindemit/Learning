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
            SetupZoom(0.1f, 2f);
            
            this.AddManipulator(m_SelectionDragger);
            this.AddManipulator(m_Selector);
        }

    }

    public class PortDataOne { }
    public class PortDataTwo { }
    public class PortDataThree { }

    public class DraggableBox : GraphElement
    {
        public DraggableBox()
        {
            name = "DraggableBox";

            //var tpl = EditorGUIUtility.Load("UXML/GraphView/Node.uxml") as VisualTreeAsset;
            var my = EditorGUIUtility.Load("Assets/Editor/Resources/FlexBasisTest.uxml") as VisualTreeAsset;

            my.CloneTree(this, new System.Collections.Generic.Dictionary<string, VisualElement>());
            //EditorGUIUtility.
            //var titleLable = this.Q<Label>(name: "title-label");
            //titleLable.AddToClassList("draggableBoxTitle");

            SetSize(new Vector2(400, 700));
            capabilities =
                Capabilities.Selectable |
                Capabilities.Collapsible |
                Capabilities.Resizable |
                Capabilities.Movable |
                Capabilities.Deletable |
                Capabilities.Droppable |
                Capabilities.Ascendable;

            //title = "Floating Box";
            AddPorts(typeof(PortDataOne));
            AddPorts(typeof(PortDataTwo));
            AddPorts(typeof(PortDataThree));

            /*mainContainer.Add(new Label("Test message 1"));
            mainContainer.Add(new Label("Test message 2"));
            mainContainer.Add(new Label("Test message 3"));
            mainContainer.Add(new Label("Test message 4"));
            mainContainer.Add(new Label("Test message 5"));
            mainContainer.Add(new Label("Test message 6"));
            mainContainer.Add(new Label("Test message 7"));
            mainContainer.Add(new Label("Test message 8"));
            mainContainer.Add(new Label("Test message 9"));
            mainContainer.Add(new Label("Test message 10"));
            mainContainer.Add(new Label("Test message 11"));
            mainContainer.Add(new Label("Test message 12"));*/
        }

        private void AddPorts(Type type)
        {
            //inputContainer.Add(InstantiatePort(Orientation.Horizontal, Direction.Input, Port.Capacity.Multi, type));
            //outputContainer.Add(InstantiatePort(Orientation.Horizontal, Direction.Output, Port.Capacity.Multi, type));
        }
    }



    public class E08_EditorControls : EditorWindow
    {
        private WorkSpace m_WorkSpace;

        private void OnEnable()
        {
            VisualElement m_Root = this.GetRootVisualContainer();
            m_Root.AddStyleSheetPath("mystyles");
            m_Root.AddToClassList("rootClass");

            BuildWorkspace(m_Root);
        }
        private void OnFocus()
        {
            BuildWorkspace(this.GetRootVisualContainer());
        }
        private void OnGUI()
        {
            if (Event.current.type == EventType.Layout)
            {
                m_WorkSpace.SetSize(new Vector2(position.width, position.height));
            }

        }

        private void BuildWorkspace(VisualElement root)
        {
            root.Clear();
            m_WorkSpace = new WorkSpace();
            root.Add(m_WorkSpace);

            const int itemsCount = 1;
            for (int i = 0; i < itemsCount; i++)
            {
                DraggableBox db = new DraggableBox();
                db.transform.position = new Vector3(i * (db.layout.width + 20), 0);
                m_WorkSpace.AddElement(db);
            }
        }

        [MenuItem("UIElementsExamples/08_Nodes")]
        public static void ShowExample()
        {
            var window = GetWindow<E08_EditorControls>();
            window.minSize = new Vector2(300, 300);
            window.titleContent = new GUIContent("Example 8");
        }
    }
}
