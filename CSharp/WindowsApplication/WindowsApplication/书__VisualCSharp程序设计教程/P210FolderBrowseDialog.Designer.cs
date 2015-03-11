namespace WindowsApplication
{
    partial class P210FolderBrowseDialog
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
            this.lblIntroduce = new System.Windows.Forms.Label();
            this.txtContent = new System.Windows.Forms.RichTextBox();
            this.lblName = new System.Windows.Forms.Label();
            this.lblPosition = new System.Windows.Forms.Label();
            this.lblType = new System.Windows.Forms.Label();
            this.txtName = new System.Windows.Forms.TextBox();
            this.txtPosition = new System.Windows.Forms.TextBox();
            this.cbType = new System.Windows.Forms.ComboBox();
            this.lblBrowse = new System.Windows.Forms.Button();
            this.bntOk = new System.Windows.Forms.Button();
            this.bntCancel = new System.Windows.Forms.Button();
            this.folder = new System.Windows.Forms.FolderBrowserDialog();
            this.SuspendLayout();
            // 
            // lblIntroduce
            // 
            this.lblIntroduce.AutoSize = true;
            this.lblIntroduce.Location = new System.Drawing.Point(13, 13);
            this.lblIntroduce.Name = "lblIntroduce";
            this.lblIntroduce.Size = new System.Drawing.Size(65, 12);
            this.lblIntroduce.TabIndex = 0;
            this.lblIntroduce.Text = "个人简历: ";
            // 
            // txtContent
            // 
            this.txtContent.Location = new System.Drawing.Point(15, 28);
            this.txtContent.Name = "txtContent";
            this.txtContent.Size = new System.Drawing.Size(541, 216);
            this.txtContent.TabIndex = 1;
            this.txtContent.Text = "";
            // 
            // lblName
            // 
            this.lblName.AutoSize = true;
            this.lblName.Location = new System.Drawing.Point(13, 263);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(41, 12);
            this.lblName.TabIndex = 0;
            this.lblName.Text = "名称: ";
            // 
            // lblPosition
            // 
            this.lblPosition.AutoSize = true;
            this.lblPosition.Location = new System.Drawing.Point(13, 295);
            this.lblPosition.Name = "lblPosition";
            this.lblPosition.Size = new System.Drawing.Size(41, 12);
            this.lblPosition.TabIndex = 0;
            this.lblPosition.Text = "位置: ";
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point(333, 263);
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size(41, 12);
            this.lblType.TabIndex = 0;
            this.lblType.Text = "类型: ";
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(60, 260);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(267, 21);
            this.txtName.TabIndex = 2;
            // 
            // txtPosition
            // 
            this.txtPosition.Location = new System.Drawing.Point(60, 292);
            this.txtPosition.Name = "txtPosition";
            this.txtPosition.Size = new System.Drawing.Size(415, 21);
            this.txtPosition.TabIndex = 2;
            // 
            // cbType
            // 
            this.cbType.FormattingEnabled = true;
            this.cbType.Items.AddRange(new object[] {
            "文本文件,*.txt",
            "网页文件,*.htm"});
            this.cbType.Location = new System.Drawing.Point(380, 260);
            this.cbType.Name = "cbType";
            this.cbType.Size = new System.Drawing.Size(176, 20);
            this.cbType.TabIndex = 3;
            // 
            // lblBrowse
            // 
            this.lblBrowse.Location = new System.Drawing.Point(481, 290);
            this.lblBrowse.Name = "lblBrowse";
            this.lblBrowse.Size = new System.Drawing.Size(75, 23);
            this.lblBrowse.TabIndex = 4;
            this.lblBrowse.Text = "浏览";
            this.lblBrowse.UseVisualStyleBackColor = true;
            this.lblBrowse.Click += new System.EventHandler(this.lblBrowse_Click);
            // 
            // bntOk
            // 
            this.bntOk.Location = new System.Drawing.Point(130, 332);
            this.bntOk.Name = "bntOk";
            this.bntOk.Size = new System.Drawing.Size(75, 23);
            this.bntOk.TabIndex = 4;
            this.bntOk.Text = "确定";
            this.bntOk.UseVisualStyleBackColor = true;
            this.bntOk.Click += new System.EventHandler(this.bntOk_Click);
            // 
            // bntCancel
            // 
            this.bntCancel.Location = new System.Drawing.Point(358, 332);
            this.bntCancel.Name = "bntCancel";
            this.bntCancel.Size = new System.Drawing.Size(75, 23);
            this.bntCancel.TabIndex = 4;
            this.bntCancel.Text = "取消";
            this.bntCancel.UseVisualStyleBackColor = true;
            this.bntCancel.Click += new System.EventHandler(this.bntCancel_Click);
            // 
            // P210FolderBrowseDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(568, 384);
            this.Controls.Add(this.bntCancel);
            this.Controls.Add(this.bntOk);
            this.Controls.Add(this.lblBrowse);
            this.Controls.Add(this.cbType);
            this.Controls.Add(this.txtPosition);
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.txtContent);
            this.Controls.Add(this.lblPosition);
            this.Controls.Add(this.lblType);
            this.Controls.Add(this.lblName);
            this.Controls.Add(this.lblIntroduce);
            this.Name = "P210FolderBrowseDialog";
            this.Text = "P210FolderBrowseDialog";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblIntroduce;
        private System.Windows.Forms.RichTextBox txtContent;
        private System.Windows.Forms.Label lblName;
        private System.Windows.Forms.Label lblPosition;
        private System.Windows.Forms.Label lblType;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.TextBox txtPosition;
        private System.Windows.Forms.ComboBox cbType;
        private System.Windows.Forms.Button lblBrowse;
        private System.Windows.Forms.Button bntOk;
        private System.Windows.Forms.Button bntCancel;
        private System.Windows.Forms.FolderBrowserDialog folder;
    }
}