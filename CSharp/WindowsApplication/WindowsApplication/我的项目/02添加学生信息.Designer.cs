namespace WindowsApplication.我的项目
{
    partial class _02添加学生信息
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
            this.txtBoxAddress = new System.Windows.Forms.TextBox();
            this.rbntMan = new System.Windows.Forms.RadioButton();
            this.rbntWoman = new System.Windows.Forms.RadioButton();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtBoxName = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.bntOk = new System.Windows.Forms.Button();
            this.bntDel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("黑体", 14F);
            this.label1.Location = new System.Drawing.Point(12, 166);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(69, 19);
            this.label1.TabIndex = 0;
            this.label1.Text = "地址: ";
            // 
            // txtBoxAddress
            // 
            this.txtBoxAddress.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtBoxAddress.Font = new System.Drawing.Font("黑体", 14F);
            this.txtBoxAddress.Location = new System.Drawing.Point(88, 163);
            this.txtBoxAddress.Multiline = true;
            this.txtBoxAddress.Name = "txtBoxAddress";
            this.txtBoxAddress.Size = new System.Drawing.Size(205, 81);
            this.txtBoxAddress.TabIndex = 1;
            // 
            // rbntMan
            // 
            this.rbntMan.AutoSize = true;
            this.rbntMan.Font = new System.Drawing.Font("黑体", 14F);
            this.rbntMan.Location = new System.Drawing.Point(47, 58);
            this.rbntMan.Name = "rbntMan";
            this.rbntMan.Size = new System.Drawing.Size(47, 23);
            this.rbntMan.TabIndex = 2;
            this.rbntMan.TabStop = true;
            this.rbntMan.Text = "男";
            this.rbntMan.UseVisualStyleBackColor = true;
            // 
            // rbntWoman
            // 
            this.rbntWoman.AutoSize = true;
            this.rbntWoman.Font = new System.Drawing.Font("黑体", 14F);
            this.rbntWoman.Location = new System.Drawing.Point(139, 58);
            this.rbntWoman.Name = "rbntWoman";
            this.rbntWoman.Size = new System.Drawing.Size(47, 23);
            this.rbntWoman.TabIndex = 2;
            this.rbntWoman.TabStop = true;
            this.rbntWoman.Text = "女";
            this.rbntWoman.UseVisualStyleBackColor = true;
            // 
            // comboBox1
            // 
            this.comboBox1.Font = new System.Drawing.Font("黑体", 14F);
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "汉族",
            "回族",
            "满族",
            "其他"});
            this.comboBox1.Location = new System.Drawing.Point(88, 130);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(124, 27);
            this.comboBox1.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("黑体", 14F);
            this.label2.Location = new System.Drawing.Point(13, 133);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 19);
            this.label2.TabIndex = 0;
            this.label2.Text = "民族: ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("黑体", 14F);
            this.label3.Location = new System.Drawing.Point(13, 98);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(69, 19);
            this.label3.TabIndex = 0;
            this.label3.Text = "生日: ";
            // 
            // txtBoxName
            // 
            this.txtBoxName.Font = new System.Drawing.Font("黑体", 14F);
            this.txtBoxName.Location = new System.Drawing.Point(88, 12);
            this.txtBoxName.Name = "txtBoxName";
            this.txtBoxName.Size = new System.Drawing.Size(124, 29);
            this.txtBoxName.TabIndex = 5;
            this.txtBoxName.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtBoxName.TextChanged += new System.EventHandler(this.txtBoxName_TextChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("黑体", 14F);
            this.label4.Location = new System.Drawing.Point(13, 15);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 19);
            this.label4.TabIndex = 4;
            this.label4.Text = "姓名: ";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(89, 98);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(123, 21);
            this.dateTimePicker1.TabIndex = 6;
            // 
            // bntOk
            // 
            this.bntOk.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bntOk.Font = new System.Drawing.Font("黑体", 14F);
            this.bntOk.Location = new System.Drawing.Point(218, 12);
            this.bntOk.Name = "bntOk";
            this.bntOk.Size = new System.Drawing.Size(75, 69);
            this.bntOk.TabIndex = 7;
            this.bntOk.Text = "Ok";
            this.bntOk.UseVisualStyleBackColor = true;
            this.bntOk.Click += new System.EventHandler(this.bntOk_Click);
            // 
            // bntDel
            // 
            this.bntDel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.bntDel.Font = new System.Drawing.Font("黑体", 14F);
            this.bntDel.ForeColor = System.Drawing.Color.Red;
            this.bntDel.Location = new System.Drawing.Point(218, 90);
            this.bntDel.Name = "bntDel";
            this.bntDel.Size = new System.Drawing.Size(75, 67);
            this.bntDel.TabIndex = 7;
            this.bntDel.Text = "删除";
            this.bntDel.UseVisualStyleBackColor = true;
            this.bntDel.Visible = false;
            this.bntDel.Click += new System.EventHandler(this.bntDel_Click);
            // 
            // _02添加学生信息
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(305, 261);
            this.Controls.Add(this.bntDel);
            this.Controls.Add(this.bntOk);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.txtBoxName);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.rbntWoman);
            this.Controls.Add(this.rbntMan);
            this.Controls.Add(this.txtBoxAddress);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "_02添加学生信息";
            this.Opacity = 0.9D;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "添加学生信息";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this._02添加学生信息_FormClosed);
            this.Load += new System.EventHandler(this._02添加学生信息_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtBoxAddress;
        private System.Windows.Forms.RadioButton rbntMan;
        private System.Windows.Forms.RadioButton rbntWoman;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtBoxName;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Button bntOk;
        private System.Windows.Forms.Button bntDel;
    }
}