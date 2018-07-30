using System;
using UnityEditor;
using UnityEngine;
using UnityEngine.Experimental.UIElements;
using UnityEditor.Experimental.UIElements;
using UnityEditor.Experimental.UIElements.GraphView;
using Object = UnityEngine.Object;

namespace UIElementsExamples
{
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


            /*Texture2D backgroundTexrure = AssetDatabase.LoadAssetAtPath<Texture2D>("Assets/Textures/background.png");
            var image = new Image()
            {
                image = new UnityEngine.Experimental.UIElements.StyleSheets.StyleValue<Texture>(backgroundTexrure),
                sourceRect = new Rect(0, 0, 50, 50)
            };
            boxes.Add(image);*/

            const int itemsCount = 11;
            for (int i = 0; i < itemsCount; i++)
            {
                boxes.Add(new VisualElement()
                {
                    style = { backgroundColor = new Color(1 - ((float)i / itemsCount), ((float)i / itemsCount), 0.5f)}
                });
            }
        }
    }
#endif
}
