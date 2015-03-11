namespace WindowsApplication
{
    partial class P206OpenFileDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lblFileName = new System.Windows.Forms.Label();
            this.txtFileName = new System.Windows.Forms.TextBox();
            this.bntOpen = new System.Windows.Forms.Button();
            this.lblFileContain = new System.Windows.Forms.Label();
            this.lbResult = new System.Windows.Forms.ListBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // lblFileName
            // 
            this.lblFileName.AutoSize = true;
            this.lblFileName.Location = new System.Drawing.Point(13, 13);
            this.lblFileName.Name = "lblFileName";
            this.lblFileName.Size = new System.Drawing.Size(53, 12);
            this.lblFileName.TabIndex = 0;
            this.lblFileName.Text = "文件名: ";
            // 
            // txtFileName
            // 
            this.txtFileName.Location = new System.Drawing.Point(62, 10);
            this.txtFileName.Name = "txtFileName";
            this.txtFileName.Size = new System.Drawing.Size(138, 21);
            this.txtFileName.TabIndex = 1;
            // 
            // bntOpen
            // 
            this.bntOpen.Location = new System.Drawing.Point(206, 10);
            this.bntOpen.Name = "bntOpen";
            this.bntOpen.Size = new System.Drawing.Size(75, 23);
            this.bntOpen.TabIndex = 2;
            this.bntOpen.Text = "打开";
            this.bntOpen.UseVisualStyleBackColor = true;
            this.bntOpen.Click += new System.EventHandler(this.bntOpen_Click);
            // 
            // lblFileContain
            // 
            this.lblFileContain.AutoSize = true;
            this.lblFileContain.Location = new System.Drawing.Point(13, 46);
            this.lblFileContain.Name = "lblFileContain";
            this.lblFileContain.Size = new System.Drawing.Size(125, 12);
            this.lblFileContain.TabIndex = 0;
            this.lblFileContain.Text = "该文件包含以下数据: ";
            // 
            // lbResult
            // 
            this.lbResult.FormattingEnabled = true;
            this.lbResult.ItemHeight = 12;
            this.lbResult.Items.AddRange(new object[] {
            "学号        姓名        系别"});
            this.lbResult.Location = new System.Drawing.Point(18, 73);
            this.lbResult.Name = "lbResult";
            this.lbResult.Size = new System.Drawing.Size(263, 172);
            this.lbResult.TabIndex = 3;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "数据文件,*.dat|*.dat|所有文件,*.*|*.*";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // P206OpenFileDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(296, 262);
            this.Controls.Add(this.lbResult);
            this.Controls.Add(this.bntOpen);
            this.Controls.Add(this.txtFileName);
            this.Controls.Add(this.lblFileContain);
            this.Controls.Add(this.lblFileName);
            this.Name = "P206OpenFileDialog";
            this.Text = "P206OpenFileDialog";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblFileName;
        private System.Windows.Forms.TextBox txtFileName;
        private System.Windows.Forms.Button bntOpen;
        private System.Windows.Forms.Label lblFileContain;
        private System.Windows.Forms.ListBox lbResult;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
    }
}