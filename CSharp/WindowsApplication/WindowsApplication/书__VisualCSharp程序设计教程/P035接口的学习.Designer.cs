namespace WindowsApplication
{
    partial class P035接口的学习
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
            this.numBtn = new System.Windows.Forms.Label();
            this.nameLbl = new System.Windows.Forms.Label();
            this.numTxtBox = new System.Windows.Forms.TextBox();
            this.nameTxtBox = new System.Windows.Forms.TextBox();
            this.okBnt = new System.Windows.Forms.Button();
            this.showLbl = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // numBtn
            // 
            this.numBtn.AutoSize = true;
            this.numBtn.Location = new System.Drawing.Point(53, 65);
            this.numBtn.Name = "numBtn";
            this.numBtn.Size = new System.Drawing.Size(23, 12);
            this.numBtn.TabIndex = 0;
            this.numBtn.Text = "Num";
            // 
            // nameLbl
            // 
            this.nameLbl.AutoSize = true;
            this.nameLbl.Location = new System.Drawing.Point(53, 126);
            this.nameLbl.Name = "nameLbl";
            this.nameLbl.Size = new System.Drawing.Size(29, 12);
            this.nameLbl.TabIndex = 0;
            this.nameLbl.Text = "Name";
            // 
            // numTxtBox
            // 
            this.numTxtBox.Location = new System.Drawing.Point(100, 62);
            this.numTxtBox.Name = "numTxtBox";
            this.numTxtBox.Size = new System.Drawing.Size(100, 21);
            this.numTxtBox.TabIndex = 1;
            // 
            // nameTxtBox
            // 
            this.nameTxtBox.Location = new System.Drawing.Point(100, 123);
            this.nameTxtBox.Name = "nameTxtBox";
            this.nameTxtBox.Size = new System.Drawing.Size(100, 21);
            this.nameTxtBox.TabIndex = 1;
            // 
            // okBnt
            // 
            this.okBnt.Location = new System.Drawing.Point(100, 165);
            this.okBnt.Name = "okBnt";
            this.okBnt.Size = new System.Drawing.Size(75, 23);
            this.okBnt.TabIndex = 2;
            this.okBnt.Text = "Ok";
            this.okBnt.UseVisualStyleBackColor = true;
            this.okBnt.Click += new System.EventHandler(this.okBnt_Click);
            // 
            // showLbl
            // 
            this.showLbl.AutoSize = true;
            this.showLbl.Location = new System.Drawing.Point(53, 205);
            this.showLbl.Name = "showLbl";
            this.showLbl.Size = new System.Drawing.Size(101, 12);
            this.showLbl.TabIndex = 0;
            this.showLbl.Text = "Input your info.";
            // 
            // P035接口的学习
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.okBnt);
            this.Controls.Add(this.nameTxtBox);
            this.Controls.Add(this.numTxtBox);
            this.Controls.Add(this.nameLbl);
            this.Controls.Add(this.showLbl);
            this.Controls.Add(this.numBtn);
            this.Name = "P035接口的学习";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.P035接口的学习_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label numBtn;
        private System.Windows.Forms.Label nameLbl;
        private System.Windows.Forms.TextBox numTxtBox;
        private System.Windows.Forms.TextBox nameTxtBox;
        private System.Windows.Forms.Button okBnt;
        private System.Windows.Forms.Label showLbl;
    }
}