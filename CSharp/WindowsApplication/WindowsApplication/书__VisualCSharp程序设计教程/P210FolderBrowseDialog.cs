// Build: 2014-9-25 20:25:23
using System.IO;
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
    public partial class P210FolderBrowseDialog : Form
    {
        public P210FolderBrowseDialog()
        {
            InitializeComponent();
        }

        private void lblBrowse_Click(object sender, EventArgs e)
        {
            DialogResult result = folder.ShowDialog();
            if (result == DialogResult.OK)
                txtPosition.Text = folder.SelectedPath;
        }

        private void bntOk_Click(object sender, EventArgs e)
        {
            string path = String.Format(@"{0}\{1}.txt", txtPosition.Text, txtName.Text);
            Stream stream = new FileStream(path, FileMode.OpenOrCreate, FileAccess.Write);
            StreamWriter sw = new StreamWriter(stream);
            sw.Write(txtContent.Text);
            sw.Close();
            stream.Close();

        }

        private void bntCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        
    }
}
