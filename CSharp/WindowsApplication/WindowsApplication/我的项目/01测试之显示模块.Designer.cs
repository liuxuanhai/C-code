namespace WindowsApplication
{
    partial class 显示模块测试
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.AppendLineBnt = new System.Windows.Forms.Button();
            this.PushCharBnt = new System.Windows.Forms.Button();
            this.PopCharBnt = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("黑体", 14F);
            this.textBox1.Location = new System.Drawing.Point(13, 13);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.textBox1.Size = new System.Drawing.Size(293, 53);
            this.textBox1.TabIndex = 0;
            // 
            // AppendLineBnt
            // 
            this.AppendLineBnt.Location = new System.Drawing.Point(12, 103);
            this.AppendLineBnt.Name = "AppendLineBnt";
            this.AppendLineBnt.Size = new System.Drawing.Size(109, 23);
            this.AppendLineBnt.TabIndex = 1;
            this.AppendLineBnt.Text = "AppendLine(\"1\")";
            this.AppendLineBnt.UseVisualStyleBackColor = true;
            this.AppendLineBnt.Click += new System.EventHandler(this.AppendLineBnt_Click);
            // 
            // PushCharBnt
            // 
            this.PushCharBnt.Location = new System.Drawing.Point(127, 103);
            this.PushCharBnt.Name = "PushCharBnt";
            this.PushCharBnt.Size = new System.Drawing.Size(98, 23);
            this.PushCharBnt.TabIndex = 2;
            this.PushCharBnt.Text = "PushChar(\"+\")";
            this.PushCharBnt.UseVisualStyleBackColor = true;
            this.PushCharBnt.Click += new System.EventHandler(this.PushCharBnt_Click);
            // 
            // PopCharBnt
            // 
            this.PopCharBnt.Location = new System.Drawing.Point(231, 103);
            this.PopCharBnt.Name = "PopCharBnt";
            this.PopCharBnt.Size = new System.Drawing.Size(75, 23);
            this.PopCharBnt.TabIndex = 2;
            this.PopCharBnt.Text = "PopChar()";
            this.PopCharBnt.UseVisualStyleBackColor = true;
            this.PopCharBnt.Click += new System.EventHandler(this.PopCharBnt_Click);
            // 
            // 显示模块测试
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(320, 157);
            this.Controls.Add(this.PopCharBnt);
            this.Controls.Add(this.PushCharBnt);
            this.Controls.Add(this.AppendLineBnt);
            this.Controls.Add(this.textBox1);
            this.Name = "显示模块测试";
            this.Text = "显示模块测试";
            this.Load += new System.EventHandler(this.HeabCalculator1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button AppendLineBnt;
        private System.Windows.Forms.Button PushCharBnt;
        private System.Windows.Forms.Button PopCharBnt;
    }
}