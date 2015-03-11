// Build: ‎2014‎-09‎-18‎ ‏‎10:00:21

// VS2012会根据程序员的操作自动更新Main方法中的语句, 因此, 程序员不需要在Main方法中添加任何代码
// 窗体代码中的partial关键字将同一个窗体的代码分开放在两个文件中
//      1.  vs2012自动生成的代码在.Designer.cs中
//      2.  用户自己编写的代码在.cs中


using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using WindowsApplication.书__CSharp高级编程;
using WindowsApplication.我的项目;
using WindowsApplication.书__XML编程与应用教程;

namespace WindowsApplication
{
    static class HelloWorldMain
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();   // 启动程序的可视样式
            Application.SetCompatibleTextRenderingDefault(false);
            #region 书 VisualCSharp程序设计
            //Application.Run(new P015HelloWorldFrm());
            //Application.Run(new P035接口的学习());
            //Application.Run(new P146windows窗体与事件驱动());
            //Application.Run(new P159Login());
            //Application.Run(new P164StudentMsgFrm());
            //Application.Run(new P167CourseMsgFrm());
            //Application.Run(new P170AboutForm());
            //Application.Run(new P176MainFrm());
            //Application.Run(new P179三种对话框());
            //Application.Run(new P184一个文本编辑器());
            //Application.Run(new P200读写文本文件());
            //Application.Run(new P202读写二进制文件());
            //Application.Run(new P203对象的序列化());
            //Application.Run(new P206OpenFileDialog());
            //Application.Run(new P210FolderBrowseDialog());
            #endregion
            #region 书 CSharp高级编程
            //Application.Run(new P1190TextBox控件());
            #endregion
            #region 书 XML编程与应用教程
            //Application.Run(new P274XmlDOM的学习());
            #endregion
            #region 我的项目
            //Application.Run(new 显示模块测试());
            Application.Run(new _02学生管理系统());
            //Application.Run(new _02添加学生信息());
            #endregion
        }
    }
}
