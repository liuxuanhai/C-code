namespace WindowsApplication
{
    partial class P176MainFrm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(P176MainFrm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.tsmSysteMsg = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmExit = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmStudentMsg = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmNewStudent = new System.Windows.Forms.ToolStripMenuItem();
            this.学生信息管理SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmCourseMsg = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmNewCourse = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmCurMsgMag = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmScoreMsg = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.复制CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.粘贴PToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.删除DToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbNewStudent = new System.Windows.Forms.ToolStripButton();
            this.tsbStuMsgMag = new System.Windows.Forms.ToolStripButton();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.tssStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.tssMsg = new System.Windows.Forms.ToolStripStatusLabel();
            this.menuStrip1.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmSysteMsg,
            this.tsmStudentMsg,
            this.tsmCourseMsg,
            this.tsmScoreMsg,
            this.tsmHelp});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(602, 25);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // tsmSysteMsg
            // 
            this.tsmSysteMsg.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmExit});
            this.tsmSysteMsg.Name = "tsmSysteMsg";
            this.tsmSysteMsg.Size = new System.Drawing.Size(83, 21);
            this.tsmSysteMsg.Text = "系统管理(&S)";
            // 
            // tsmExit
            // 
            this.tsmExit.Image = global::WindowsApplication.Properties.Resources.exit;
            this.tsmExit.Name = "tsmExit";
            this.tsmExit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.E)));
            this.tsmExit.Size = new System.Drawing.Size(159, 22);
            this.tsmExit.Text = "退出(&E)";
            this.tsmExit.Click += new System.EventHandler(this.tsmExit_Click);
            // 
            // tsmStudentMsg
            // 
            this.tsmStudentMsg.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmNewStudent,
            this.学生信息管理SToolStripMenuItem});
            this.tsmStudentMsg.Name = "tsmStudentMsg";
            this.tsmStudentMsg.Size = new System.Drawing.Size(83, 21);
            this.tsmStudentMsg.Text = "学生管理(&S)";
            // 
            // tsmNewStudent
            // 
            this.tsmNewStudent.Image = global::WindowsApplication.Properties.Resources.newStu;
            this.tsmNewStudent.Name = "tsmNewStudent";
            this.tsmNewStudent.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.tsmNewStudent.Size = new System.Drawing.Size(251, 22);
            this.tsmNewStudent.Text = "添加学生信息(&A)...";
            this.tsmNewStudent.Click += new System.EventHandler(this.tsmNewStudent_Click);
            // 
            // 学生信息管理SToolStripMenuItem
            // 
            this.学生信息管理SToolStripMenuItem.Image = global::WindowsApplication.Properties.Resources.setting;
            this.学生信息管理SToolStripMenuItem.Name = "学生信息管理SToolStripMenuItem";
            this.学生信息管理SToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.学生信息管理SToolStripMenuItem.Size = new System.Drawing.Size(251, 22);
            this.学生信息管理SToolStripMenuItem.Text = "学生信息管理(&S)...";
            // 
            // tsmCourseMsg
            // 
            this.tsmCourseMsg.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmNewCourse,
            this.tsmCurMsgMag});
            this.tsmCourseMsg.Name = "tsmCourseMsg";
            this.tsmCourseMsg.Size = new System.Drawing.Size(84, 21);
            this.tsmCourseMsg.Text = "课程管理(&C)";
            // 
            // tsmNewCourse
            // 
            this.tsmNewCourse.Image = global::WindowsApplication.Properties.Resources.add;
            this.tsmNewCourse.Name = "tsmNewCourse";
            this.tsmNewCourse.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.C)));
            this.tsmNewCourse.Size = new System.Drawing.Size(228, 22);
            this.tsmNewCourse.Text = "添加课程(&A)...";
            this.tsmNewCourse.Click += new System.EventHandler(this.tsmNewCourse_Click);
            // 
            // tsmCurMsgMag
            // 
            this.tsmCurMsgMag.Image = global::WindowsApplication.Properties.Resources.setting;
            this.tsmCurMsgMag.Name = "tsmCurMsgMag";
            this.tsmCurMsgMag.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.tsmCurMsgMag.Size = new System.Drawing.Size(228, 22);
            this.tsmCurMsgMag.Text = "课程信息管理(&C)...";
            // 
            // tsmScoreMsg
            // 
            this.tsmScoreMsg.Name = "tsmScoreMsg";
            this.tsmScoreMsg.Size = new System.Drawing.Size(84, 21);
            this.tsmScoreMsg.Text = "成绩管理(&A)";
            // 
            // tsmHelp
            // 
            this.tsmHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmAbout});
            this.tsmHelp.Name = "tsmHelp";
            this.tsmHelp.Size = new System.Drawing.Size(61, 21);
            this.tsmHelp.Text = "帮助(&H)";
            // 
            // tsmAbout
            // 
            this.tsmAbout.Image = global::WindowsApplication.Properties.Resources.panda;
            this.tsmAbout.Name = "tsmAbout";
            this.tsmAbout.Size = new System.Drawing.Size(152, 22);
            this.tsmAbout.Text = "关于(&A)...";
            this.tsmAbout.Click += new System.EventHandler(this.tsmAbout_Click);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.复制CToolStripMenuItem,
            this.粘贴PToolStripMenuItem,
            this.删除DToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(118, 70);
            // 
            // 复制CToolStripMenuItem
            // 
            this.复制CToolStripMenuItem.Name = "复制CToolStripMenuItem";
            this.复制CToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.复制CToolStripMenuItem.Text = "复制(&C)";
            // 
            // 粘贴PToolStripMenuItem
            // 
            this.粘贴PToolStripMenuItem.Name = "粘贴PToolStripMenuItem";
            this.粘贴PToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.粘贴PToolStripMenuItem.Text = "粘贴(&P)";
            // 
            // 删除DToolStripMenuItem
            // 
            this.删除DToolStripMenuItem.Name = "删除DToolStripMenuItem";
            this.删除DToolStripMenuItem.Size = new System.Drawing.Size(117, 22);
            this.删除DToolStripMenuItem.Text = "删除(&D)";
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbNewStudent,
            this.tsbStuMsgMag});
            this.toolStrip1.Location = new System.Drawing.Point(0, 25);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(602, 39);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbNewStudent
            // 
            this.tsbNewStudent.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbNewStudent.Image = global::WindowsApplication.Properties.Resources.newStu;
            this.tsbNewStudent.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbNewStudent.Name = "tsbNewStudent";
            this.tsbNewStudent.Size = new System.Drawing.Size(36, 36);
            this.tsbNewStudent.Text = "添加学生信息";
            this.tsbNewStudent.Click += new System.EventHandler(this.tsmNewStudent_Click);
            // 
            // tsbStuMsgMag
            // 
            this.tsbStuMsgMag.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbStuMsgMag.Image = global::WindowsApplication.Properties.Resources.contacts;
            this.tsbStuMsgMag.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbStuMsgMag.Name = "tsbStuMsgMag";
            this.tsbStuMsgMag.Size = new System.Drawing.Size(36, 36);
            this.tsbStuMsgMag.Text = "学生信息管理";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tssStatus,
            this.tssMsg});
            this.statusStrip1.Location = new System.Drawing.Point(0, 395);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(602, 22);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // tssStatus
            // 
            this.tssStatus.Image = global::WindowsApplication.Properties.Resources.panda;
            this.tssStatus.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tssStatus.Name = "tssStatus";
            this.tssStatus.Size = new System.Drawing.Size(293, 17);
            this.tssStatus.Spring = true;
            this.tssStatus.Text = "就绪";
            this.tssStatus.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tssMsg
            // 
            this.tssMsg.Name = "tssMsg";
            this.tssMsg.Size = new System.Drawing.Size(293, 17);
            this.tssMsg.Spring = true;
            this.tssMsg.Text = "请选择一个操作";
            this.tssMsg.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // P176MainFrm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(602, 417);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "P176MainFrm";
            this.Text = "MainFrm";
            this.Load += new System.EventHandler(this.P176MainFrm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem tsmSysteMsg;
        private System.Windows.Forms.ToolStripMenuItem tsmExit;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 复制CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 粘贴PToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 删除DToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripMenuItem tsmStudentMsg;
        private System.Windows.Forms.ToolStripMenuItem tsmCourseMsg;
        private System.Windows.Forms.ToolStripMenuItem tsmScoreMsg;
        private System.Windows.Forms.ToolStripMenuItem tsmHelp;
        private System.Windows.Forms.ToolStripMenuItem tsmNewStudent;
        private System.Windows.Forms.ToolStripMenuItem 学生信息管理SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tsmNewCourse;
        private System.Windows.Forms.ToolStripMenuItem tsmCurMsgMag;
        private System.Windows.Forms.ToolStripMenuItem tsmAbout;
        private System.Windows.Forms.ToolStripButton tsbNewStudent;
        private System.Windows.Forms.ToolStripButton tsbStuMsgMag;
        private System.Windows.Forms.ToolStripStatusLabel tssStatus;
        private System.Windows.Forms.ToolStripStatusLabel tssMsg;
    }
}