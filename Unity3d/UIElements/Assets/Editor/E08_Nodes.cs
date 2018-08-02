using System;
using UnityEditor;
using UnityEngine;
using UnityEngine.Experimental.UIElements;
using UnityEditor.Experimental.UIElements;
using UnityEditor.Experimental.UIElements.GraphView;
using Object = UnityEngine.Object;
using System.Collections.Generic;

namespace UIElementsExamples
{
    public class CustomDragger : Dragger
    {
        public CustomDragger()
        {
        }
    }

    public class DraggableBox : GraphView
    {
        readonly Label m_Label;
        private readonly CustomDragger m_Dragger;
        public DraggableBox()
        {
            SetSize(new Vector2(300, 300));

            m_Dragger = new CustomDragger { clampToParentEdges = false };
            this.AddManipulator(m_Dragger);

            m_Label = new Label("Floating Box");
            AddToClassList("draggablebox");

            Add(m_Label);
        }
    }


#if UNITY_2018
    public class E08_EditorControls : EditorWindow
    {
        [MenuItem("UIElementsExamples/08_Nodes")]
        public static void ShowExample()
        {
            var window = GetWindow<E08_EditorControls>();
            window.minSize = new Vector2(1000, 320);
            window.titleContent = new GUIContent("Example 8");
        }

        private VisualElement m_root;
        public void OnEnable()
        {
            m_root = this.GetRootVisualContainer();
            m_root.AddStyleSheetPath("mystyles");



            var boxes = new VisualContainer() { name = "boxesContainer" };
            boxes.AddToClassList("horizontalContainer");
            m_root.Add(boxes);

            Pill pill = new Pill();
            //resizer.Add(boxes);
            m_root.Add(pill);

            DraggableBox db = new DraggableBox();
            m_root.Add(db);


            /*Texture2D backgroundTexrure = AssetDatabase.LoadAssetAtPath<Texture2D>("Assets/Textures/background.png");
            var image = new Image()
            {
                image = new UnityEngine.Experimental.UIElements.StyleSheets.StyleValue<Texture>(backgroundTexrure),
                sourceRect = new Rect(0, 0, 50, 50)
            };
            boxes.Add(image);*/

            const int itemsCount = 7;
            for (int i = 0; i < itemsCount; i++)
            {
                var box = new VisualElement()
                {
                    style = { backgroundColor = new Color(1 - ((float)i / itemsCount), ((float)i / itemsCount), 0.5f) }
                };
                box.AddToClassList("testClass");
                boxes.Add(box);
            }
        }
    }
#endif
}
