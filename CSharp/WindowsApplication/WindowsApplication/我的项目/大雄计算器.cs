using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsApplication
{

    public partial class 大雄计算器 : Form
    {        
        public 大雄计算器()
        {
            InitializeComponent();
        }

        private void 大雄计算器_Load(object sender, EventArgs e)
        {
            txtBox.Items.Add("");
        }

        private void del_Click(object sender, EventArgs e)
        {
            txtBox.Text = txtBox.Text.Remove(txtBox.Text.Length - 1, 1);
        }
        #region txtBox显示控制
        private void txtBoxTailAdd(string str)
        {
            string temp = (string)txtBox.Items[txtBox.Items.Count - 1];
            txtBox.Items[txtBox.Items.Count - 1] = temp + str;
            //txtBoxTailChanged(temp + str);
        }
        #endregion
        private void numKey_click(object sender, EventArgs e)
        {
            string str = "0123456789+-*/=";
            int i;

                    // 如果按下了数字键
            if ((i = str.IndexOf(((Button)(sender)).Text)) >= 0 && i <= 9)  // 搜寻不到返回-1
            {
                // 如果是0打头的数字, 不显示头0
                //if (txtBox.Items[txtBox.Items.Count - 1] == "" && str[i] == '0')
                //{
                    
                //}
                //else
                //{
                //    txtBoxTailAdd(str[i].ToString());
                //}
            }
                    // 如果是四则运算符
            else if (i >= 10 && i <= 13)
            {
                txtBoxTailAdd(str[i].ToString());
            }
                    // 如果是 "=" 号
            else if (i == 14)
            {
                txtBoxTailAdd(str[i].ToString());
                
                txtBox.Items.Add("result");
                // 使得窗口显示的是新加项
                txtBox.SetSelected(txtBox.Items.Count - 1, true);
                txtBox.SetSelected(txtBox.Items.Count - 1, false);
            }
        }

        private void 关于AToolStripMenuItem_Click(object sender, EventArgs e)
        {
            P170AboutForm aboutFrm = new P170AboutForm();
            aboutFrm.lblMainText = "大雄计算器";
            aboutFrm.ShowDialog();
        }
    }
}
