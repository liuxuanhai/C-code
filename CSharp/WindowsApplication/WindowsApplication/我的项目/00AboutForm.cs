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
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        }

        private void bntOk_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        #region 属性 -- 四个lable的Text设置
        public string lblMainText
        {
            set
            {
                lblMain.Text = value;
            }
        }

        public string lbl1Text
        {
            set
            {
                label1.Text = value;
            }
        }

        public string lbl2Text
        {
            set
            {
                label2.Text = value;
            }
        }

        public string lbl3Text
        {
            set
            {
                label3.Text = value;
            }
        }
        #endregion
    }
}
