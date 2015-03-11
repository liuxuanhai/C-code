namespace WindowsApplication
{
    partial class P200读写文本文件
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
            this.label1 = new System.Windows.Forms.Label();
            this.txtContent = new System.Windows.Forms.RichTextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.richTextBox2 = new System.Windows.Forms.RichTextBox();
            this.txtResult = new System.Windows.Forms.RichTextBox();
            this.bntAdd = new System.Windows.Forms.Button();
            this.bntShow = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 9);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(136, 16);
            this.label1.TabIndex = 0;
            this.label1.Text = "请输入文件内容: ";
            // 
            // txtContent
            // 
            this.txtContent.Location = new System.Drawing.Point(25, 29);
            this.txtContent.Name = "txtContent";
            this.txtContent.Size = new System.Drawing.Size(329, 96);
            this.txtContent.TabIndex = 1;
            this.txtContent.Text = "";
            // 
            // button1
            // 
            this.button1.AutoSize = true;
            this.button1.Location = new System.Drawing.Point(218, 131);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(98, 26);
            this.button1.TabIndex = 2;
            this.button1.Text = "添加到文件";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 176);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(152, 16);
            this.label2.TabIndex = 0;
            this.label2.Text = "已经成功写入文件: ";
            // 
            // richTextBox2
            // 
            this.richTextBox2.Location = new System.Drawing.Point(25, 195);
            this.richTextBox2.Name = "richTextBox2";
            this.richTextBox2.Size = new System.Drawing.Size(329, 96);
            this.richTextBox2.TabIndex = 1;
            this.richTextBox2.Text = "";
            // 
            // txtResult
            // 
            this.txtResult.Location = new System.Drawing.Point(25, 195);
            this.txtResult.Name = "txtResult";
            this.txtResult.ReadOnly = true;
            this.txtResult.Size = new System.Drawing.Size(329, 96);
            this.txtResult.TabIndex = 1;
            this.txtResult.Text = "";
            // 
            // bntAdd
            // 
            this.bntAdd.AutoSize = true;
            this.bntAdd.Location = new System.Drawing.Point(218, 131);
            this.bntAdd.Name = "bntAdd";
            this.bntAdd.Size = new System.Drawing.Size(98, 26);
            this.bntAdd.TabIndex = 2;
            this.bntAdd.Text = "添加到文件";
            this.bntAdd.UseVisualStyleBackColor = true;
            this.bntAdd.Click += new System.EventHandler(this.bntAdd_Click);
            // 
            // bntShow
            // 
            this.bntShow.AutoSize = true;
            this.bntShow.Location = new System.Drawing.Point(218, 297);
            this.bntShow.Name = "bntShow";
            this.bntShow.Size = new System.Drawing.Size(98, 26);
            this.bntShow.TabIndex = 2;
            this.bntShow.Text = "显示";
            this.bntShow.UseVisualStyleBackColor = true;
            this.bntShow.Click += new System.EventHandler(this.bntShow_Click);
            // 
            // P200读写文本文件
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 349);
            this.Controls.Add(this.bntShow);
            this.Controls.Add(this.bntAdd);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txtResult);
            this.Controls.Add(this.richTextBox2);
            this.Controls.Add(this.txtContent);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("楷体", 12F);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "P200读写文本文件";
            this.Text = "P200读写文本文件";
            this.Load += new System.EventHandler(this.P200读写文本文件_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RichTextBox txtContent;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RichTextBox richTextBox2;
        private System.Windows.Forms.RichTextBox txtResult;
        private System.Windows.Forms.Button bntAdd;
        private System.Windows.Forms.Button bntShow;
    }
}