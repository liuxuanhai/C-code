// Build: 2014-11-3 12:40:57
// 使用load方法加载文件, 流, XmlReader对象或TextReader对象中的XML数据
// 使用loadXml方法加载字符串中的Xml数据
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;   // 引入Xml的命名空间

namespace WindowsApplication.书__XML编程与应用教程
{
    public partial class P274XmlDOM的学习 : Form
    {
        public P274XmlDOM的学习()
        {
            InitializeComponent();
        }
        private XmlDocument doc;
        private void P274XlmDOM的学习_Load(object sender, EventArgs e)
        {
            
        }
        #region 显示根标签外所有Xml内容
        private void bntShowAll_Click(object sender, EventArgs e)
        {
            doc = new XmlDocument();    // 创建dom对象
            doc.Load(@"C:\Users\lenovo\Desktop\VS2013\Code\CSharp\WindowsApplication\WindowsApplication\书__XML编程与应用教程\P273XmlDOM的学习.xml");
            // 显示所有的内容
            XmlNode root = doc.DocumentElement;     // 返回解析后的树的根节点
            System.Collections.IEnumerator NodePointer = root.GetEnumerator();
            XmlNode book;
            while (NodePointer.MoveNext())          // 这里没有显示根元素<HICC></HICC>
            {
                book = (XmlNode)NodePointer.Current;
                MessageBox.Show(book.OuterXml);     
            }
        }
        #endregion
        #region 操作文本, 标签
        private void bntXmlLoad_Click(object sender, EventArgs e)
        {
            doc = new XmlDocument();
            doc.LoadXml("<book genre='novel' ISBN='1-860001-57-5'>" + 
                "<title>Pride And Prejudice</title></book>");
            // 引用book元素
            XmlNode elem = doc.DocumentElement.FirstChild;
            MessageBox.Show(elem.InnerText);    // 标签中的文本
            // 将含有标记的字符串赋给InnerText
            elem.InnerText = "Text containing <markup/> will have char(<)" +
                "and char(>) entitized.";
            MessageBox.Show(elem.OuterXml);     // 标签 + 文本
            // 将含有标记的字符串赋给InnerXml
            elem.InnerXml = "Tex containing <markup/>"; // 添加标签
            MessageBox.Show(elem.OuterXml);
        }
        #endregion
        #region 引用单个节点
        private void bntSignalNode_Click(object sender, EventArgs e)
        {
            doc = new XmlDocument();    // 创建dom对象
            doc.Load(@"C:\Users\lenovo\Desktop\VS2013\Code\CSharp\WindowsApplication\WindowsApplication\书__XML编程与应用教程\P273XmlDOM的学习.xml");
            XmlNode aNode;
            XmlElement root = doc.DocumentElement;
            aNode = root.SelectSingleNode("descendant::软件工程[@PS='何士雄']");
            MessageBox.Show(aNode.OuterXml);
        }
        #endregion
    }
}
