namespace WindowsApplication.书__XML编程与应用教程
{
    partial class P274XmlDOM的学习
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
            this.bntShowAll = new System.Windows.Forms.Button();
            this.bntXmlLoad = new System.Windows.Forms.Button();
            this.bntSignalNode = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // bntShowAll
            // 
            this.bntShowAll.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bntShowAll.Font = new System.Drawing.Font("黑体", 14F);
            this.bntShowAll.Location = new System.Drawing.Point(12, 12);
            this.bntShowAll.Name = "bntShowAll";
            this.bntShowAll.Size = new System.Drawing.Size(260, 28);
            this.bntShowAll.TabIndex = 0;
            this.bntShowAll.Text = "显示所有";
            this.bntShowAll.UseVisualStyleBackColor = true;
            this.bntShowAll.Click += new System.EventHandler(this.bntShowAll_Click);
            // 
            // bntXmlLoad
            // 
            this.bntXmlLoad.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bntXmlLoad.Font = new System.Drawing.Font("黑体", 14F);
            this.bntXmlLoad.Location = new System.Drawing.Point(12, 46);
            this.bntXmlLoad.Name = "bntXmlLoad";
            this.bntXmlLoad.Size = new System.Drawing.Size(260, 28);
            this.bntXmlLoad.TabIndex = 0;
            this.bntXmlLoad.Text = "使用XmlLoad";
            this.bntXmlLoad.UseVisualStyleBackColor = true;
            this.bntXmlLoad.Click += new System.EventHandler(this.bntXmlLoad_Click);
            // 
            // bntSignalNode
            // 
            this.bntSignalNode.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bntSignalNode.Font = new System.Drawing.Font("黑体", 14F);
            this.bntSignalNode.Location = new System.Drawing.Point(12, 80);
            this.bntSignalNode.Name = "bntSignalNode";
            this.bntSignalNode.Size = new System.Drawing.Size(260, 28);
            this.bntSignalNode.TabIndex = 0;
            this.bntSignalNode.Text = "SignalNode引用单个节点";
            this.bntSignalNode.UseVisualStyleBackColor = true;
            this.bntSignalNode.Click += new System.EventHandler(this.bntSignalNode_Click);
            // 
            // P274XmlDOM的学习
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.bntSignalNode);
            this.Controls.Add(this.bntXmlLoad);
            this.Controls.Add(this.bntShowAll);
            this.Name = "P274XmlDOM的学习";
            this.Text = "P274XmlDOM的学习";
            this.Load += new System.EventHandler(this.P274XlmDOM的学习_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button bntShowAll;
        private System.Windows.Forms.Button bntXmlLoad;
        private System.Windows.Forms.Button bntSignalNode;
    }
}