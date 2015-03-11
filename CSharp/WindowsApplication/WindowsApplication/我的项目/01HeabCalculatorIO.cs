// Build: 2014-10-20 16:54:07
// 输入输出模块实现的是:
//      1.  保存加数(初始为0), 被加数(初始为0), 操作符(初始为null)
//      1.  等于号就是输出, 按下等于号输出的情况为:
//          1.  如果操作符为null, 输出加数
//          2.  如果操作数非null, 输出加数加上上次保存的被加数
// 加: add 减: minus 乘: multiply 除: divide 
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsApplication.我的项目
{
    #region 输入输出控制模块 -- 统一控制输入输出
    class _01HeabCalculatorIO
    {
        // 显示模块的控制器
        private TxtBoxShow tbshow;
        // 计算模块的控制器
        compute c = new compute();

        private string db1Temp;
        private string db2Temp;
        private compute.Operator opeTemp;
        private enum enumStatus { db1, db2 }
        private enumStatus status;
        public _01HeabCalculatorIO(ref TextBox txtBoxShow)
        {
            db1Temp = null;
            db2Temp = null;
            opeTemp = compute.Operator.Null;
            status = enumStatus.db1;

            // 显示模块 控制器 开始接管显示器
            tbshow = new TxtBoxShow(ref txtBoxShow);
            // 初始显示一个0
            Button b = new Button();
            b.Text = "0";
            addFactor(b);
        }

        // 添加操作数
        public void addFactor(object sender)
        {
            if (enumStatus.db1 == status)
            {
                if (db1Temp == "0")
                {
                    tbshow.PopChar();
                    db1Temp = null; // 上边删除了最后一个字符以后自动将会将这行回收掉
                }
                if (db1Temp == null)
                    tbshow.AppendLine(((Button)(sender)).Text);
                else
                    tbshow.PushChar(((Button)(sender)).Text);

                db1Temp += ((Button)(sender)).Text;
            }
            else if (enumStatus.db2 == status)
            {
                tbshow.PushChar(((Button)(sender)).Text);
                db2Temp += ((Button)(sender)).Text;
            }  
        }
        // 添加操作符
        public void addOpe(object sender)
        {
            if (db1Temp == null)    // 如果没有输入左操作数就开始计算说明要以计算结果作为左操作数
            {
                db1Temp = Convert.ToString(c.Res);
            }

            if (opeTemp != compute.Operator.Null)   // 不允许 6 + 7 - 3 这种输入多个操作符的输入形式
            {
                Console.Beep(500, 500);
                return;
            }

            switch (((Button)(sender)).Text)
            {
                case "+":
                    opeTemp = compute.Operator.add;
                    break;
                case "-":
                    opeTemp = compute.Operator.minus;
                    break;
                case "×":
                    opeTemp = compute.Operator.multiply;
                    break;
                case "÷":
                    opeTemp = compute.Operator.divide;
                    break;
                case "Sin":
                    deleteDb1Temp();
                    opeTemp = compute.Operator.OpeSin;
                    break;
                case "Cos":
                    deleteDb1Temp();
                    opeTemp = compute.Operator.OpeCos;
                    break;
                case "Tan":
                    deleteDb1Temp();
                    opeTemp = compute.Operator.OpeTan;
                    break;
                case "x²":
                    opeTemp = compute.Operator.OpePingFang;
                    tbshow.PushChar("²");
                    endOne(null);
                    return;
                case "√":
                    opeTemp = compute.Operator.OpeKaiFang;
                    tbshow.PushChar("√");
                    endOne(null);
                    return;
                case "X^Y":
                    tbshow.PushChar("^");
                    status = enumStatus.db2;
                    opeTemp = compute.Operator.OpePow;
                    return;
                default:
                    break;
            }
            tbshow.PushChar(((Button)(sender)).Text);
            status = enumStatus.db2;
        }
        // 更改正负号
        public void changeFuHao()
        {
            if (enumStatus.db1 == status)
            {
                if (db1Temp == null)
                {
                    MessageBox.Show("不能随意更改结果值.");
                    return;
                }
                Button strtemp = new Button();
                strtemp.Text = Convert.ToDouble(db1Temp) > 0 ? ("-" + db1Temp) : (db1Temp.Remove(0, 1));
                deleteDb1Temp();
                addFactor(strtemp);
            }
            else if (enumStatus.db2 == status)
            {
                if (db2Temp != null)
                {
                    Button strtemp = new Button();
                    strtemp.Text = Convert.ToDouble(db2Temp) > 0 ? ("-" + db2Temp) : (db2Temp.Remove(0, 1));
                    deleteDb2Temp();
                    addFactor(strtemp);
                }
                else
                {
                    Button strtemp = new Button();
                    strtemp.Text = "-";
                    addFactor(strtemp);
                }
            }
        }
        // 删除字符
        public void delOneChar()
        {
            // status == db1 && db1Temp == null 此时用户什么都没输入
            // status == db1 && db1Temp != null 此时用户输入第一个操作数未完成
            // status == db2 && db2Temp == null 此时用户输入了左操作数和一个操作符
            // status == db2 && db2Temp != null 此时用户输入了左操作数, 操作符, 并且输入右操作数未完成
            
            if (enumStatus.db1 == status && null == db1Temp)
            {
                MessageBox.Show("没有可以删除的数据了 囧rz");
            }
            else if (enumStatus.db1 == status && null != db1Temp)
            {
                tbshow.PopChar();
                string temp = db1Temp;
                db1Temp = temp.Remove(temp.Length - 1, 1);
                if (db1Temp.Length == 0)
                    db1Temp = null;
            }
            else if (enumStatus.db2 == status && null == db2Temp)
            {
                if (opeTemp == compute.Operator.OpeSin ||
                    opeTemp == compute.Operator.OpeCos ||
                    opeTemp == compute.Operator.OpeTan)
                {
                    tbshow.PopChar();
                    tbshow.PopChar();
                    tbshow.PopChar();
                }
                else
                    tbshow.PopChar();
                // 删除一个正好把操作符删除了
                status = enumStatus.db1;
                opeTemp = compute.Operator.Null;
            }
            else if (enumStatus.db2 == status && null != db2Temp)
            {
                string temp = db2Temp;
                db2Temp = temp.Remove(temp.Length - 1, 1);
                tbshow.PopChar();
                if (db2Temp.Length == 0)
                    db2Temp = null;
            }
            else
            {
                MessageBox.Show("class _01HeabCalculatorIO => " +
                "public void delOneChar() 中出现了异常, 请联系大雄(HeabKing@qq.com)解决问题");
            }
        }
        // 操作完毕
        public void endOne(object sender)
        {
            // 将操作数交给计算模块
            try
            {
                c.Db1 = Convert.ToDouble(db1Temp);
                c.Ope = opeTemp;
                c.Db2 = Convert.ToDouble(db2Temp);
            }
            catch (System.FormatException)  // 输入 2.3.5 * 6 = ? 报错
            {
                MessageBox.Show("请按照正确的格式输入行不???");
                System.Diagnostics.Process.Start("WindowsApplication.exe");    // 启动你的程序;
                Application.Exit();                 //退出当前的程序
            }

            // 将结果显示在计算器屏幕上
            tbshow.PushChar("=");//(((Button)(sender)).Text);
            tbshow.AppendLine(Convert.ToString(c.Res));

            // 恢复初始化值
            db1Temp = null;
            db2Temp = null;
            opeTemp = compute.Operator.Null;
            status = enumStatus.db1;
        }

        private bool deleteDb1Temp()
        {
            if (enumStatus.db1 != status)
                return false;
            for (int i = 0; i < db1Temp.Length; i++)
                tbshow.PopChar();
            db1Temp = null;
            tbshow.AppendLine(" ");
            return true;
        }
        private bool deleteDb2Temp()
        {
            if (enumStatus.db2 != status)
                return false;
            for (int i = 0; i < db2Temp.Length; i++)
                tbshow.PopChar();
            db2Temp = null;
            //tbshow.AppendLine(" ");
            return true;
        }
    }
    #endregion
    #region 显示模块
    class TxtBoxShow
    {
        private TextBox textBox1;

        public TxtBoxShow(ref TextBox txtBox)
        {
            textBox1 = txtBox;
        }

        public void AppendLine(string ch)
        {
            string[] temp = new string[textBox1.Lines.Length + 1]; // 多分配一一行
            for (int i = 0; i < textBox1.Lines.Length; i++)        // 克隆原来的值
                temp[i] = textBox1.Lines[i];
            temp[textBox1.Lines.Length] = ch;          // 给新行赋值
            textBox1.Lines = temp;                      // 更新显示
            textBox1.Select(textBox1.TextLength, 0);    // 光标定位到文本最后
            textBox1.ScrollToCaret();                   // 滚动到光标处
        }

        public void PushChar(string ch)
        {
            string[] temp = new string[textBox1.Lines.Length];         // 分配一样大
            for (int i = 0; i < textBox1.Lines.Length - 1; i++)        // 克隆原来的值
                temp[i] = textBox1.Lines[i];
            if (textBox1.Lines.Length - 1 < 0)
            {
                MessageBox.Show("请确定分配了屏幕行再决定删除其中的一个字符 {{{(>_< )}}} ");
                Application.Exit();
            }
            temp[textBox1.Lines.Length - 1] = textBox1.Lines[textBox1.Lines.Length - 1] + ch;
            textBox1.Lines = temp;                      // 更新显示
            textBox1.Select(textBox1.TextLength, 0);    // 光标定位到文本最后
            textBox1.ScrollToCaret();                   // 滚动到光标处
        }

        public void PopChar()
        {
            string[] temp = new string[textBox1.Lines.Length];         // 分配一样大
            for (int i = 0; i < textBox1.Lines.Length - 1; i++)        // 克隆原来的值
                temp[i] = textBox1.Lines[i];
            try
            {
                int i1 = textBox1.Lines.Length - 1;
                int i2 = textBox1.Lines[textBox1.Lines.Length - 1].Length - 1;
                temp[i1] = textBox1.Lines[i1].Remove(i2, 1);
            }
            catch (System.ArgumentOutOfRangeException)
            {
                MessageBox.Show("你还想删除什么呢, 都叫你删干净了");
            }
            textBox1.Lines = temp;                      // 更新显示
            textBox1.Select(textBox1.TextLength, 0);    // 光标定位到文本最后
            textBox1.ScrollToCaret();                   // 滚动到光标处
        }
    }
    #endregion
    #region 计算模块
    class compute
    {
        private double db1;
        private double db2;
        private double res;
        public enum Operator { Null, add, minus, multiply, divide, OpePow,  // 加减乘除需要两个操作数db1, db2
                OpeSin, OpeCos, OpeTan,                             // 需要一个操作数db2    
                OpePingFang, OpeKaiFang                 // 需要一个操作数db1
        }
        private Operator ope;

        public compute()
        {
            db1 = 0.0;
            db2 = 0.0;
            res = 0.0;
            ope = Operator.Null;
        }

        // 计算res的值
        private double computeRes()
        {
            switch (ope)
            {
                case Operator.Null:
                    break;
                case Operator.add:
                    res = db1 + db2;
                    break;
                case Operator.minus:
                    res = db1 - db2;
                    break;
                case Operator.multiply:
                    res = db1 * db2;
                    break;
                case Operator.divide:
                    res = db1 / db2;
                    break;
                case Operator.OpeSin:
                    res = Math.Sin(db2);
                    break;
                case Operator.OpeCos:
                    res = Math.Cos(db2);
                    break;
                case Operator.OpeTan:
                    res = Math.Tan(db2);
                    break;
                case Operator.OpePingFang:
                    res = db1 * db1;
                    break;
                case Operator.OpeKaiFang:
                    res = Math.Sqrt(db1);
                    break;
                case Operator.OpePow:
                    res = Math.Pow(db1, db2);
                    break;
                default:
                    break;
            }
            return res;
        }

        public double Db1
        {
            set
            {
                db1 = value;
                //computeRes();
            }
            get 
            {
                return db1;
            }
        }
        public double Db2
        {
            set
            {
                db2 = value;
                //computeRes();
            }
            get
            {
                return db2;
            }
        }
        public Operator Ope
        {
            set
            {
                ope = value;
            }
        }
        public double Res
        {
            get
            {
                computeRes();
                return res;
            }
        }
    }
    #endregion
}
