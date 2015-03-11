namespace WindowsApplication
{
    partial class Player
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Player));
            this.mediaPlayer = new AxWMPLib.AxWindowsMediaPlayer();
            this.bntStop = new System.Windows.Forms.Button();
            this.bntStart = new System.Windows.Forms.Button();
            this.bntFullScreen = new System.Windows.Forms.Button();
            this.lblPath = new System.Windows.Forms.Label();
            this.bntPickFile = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.mediaPlayer)).BeginInit();
            this.SuspendLayout();
            // 
            // mediaPlayer
            // 
            this.mediaPlayer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.mediaPlayer.Enabled = true;
            this.mediaPlayer.Location = new System.Drawing.Point(0, 0);
            this.mediaPlayer.Name = "mediaPlayer";
            this.mediaPlayer.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("mediaPlayer.OcxState")));
            this.mediaPlayer.Size = new System.Drawing.Size(424, 219);
            this.mediaPlayer.TabIndex = 0;
            this.mediaPlayer.PlayStateChange += new AxWMPLib._WMPOCXEvents_PlayStateChangeEventHandler(this.mediaPlayer_PlayStateChange);
            // 
            // bntStop
            // 
            this.bntStop.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bntStop.AutoEllipsis = true;
            this.bntStop.Location = new System.Drawing.Point(8, 226);
            this.bntStop.Name = "bntStop";
            this.bntStop.Size = new System.Drawing.Size(75, 22);
            this.bntStop.TabIndex = 1;
            this.bntStop.Text = "Stop";
            this.bntStop.UseVisualStyleBackColor = true;
            this.bntStop.Click += new System.EventHandler(this.bntStop_Click);
            // 
            // bntStart
            // 
            this.bntStart.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bntStart.AutoEllipsis = true;
            this.bntStart.Location = new System.Drawing.Point(89, 226);
            this.bntStart.Name = "bntStart";
            this.bntStart.Size = new System.Drawing.Size(75, 22);
            this.bntStart.TabIndex = 1;
            this.bntStart.Text = "Start";
            this.bntStart.UseVisualStyleBackColor = true;
            this.bntStart.Click += new System.EventHandler(this.bntStart_Click);
            // 
            // bntFullScreen
            // 
            this.bntFullScreen.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bntFullScreen.AutoEllipsis = true;
            this.bntFullScreen.Location = new System.Drawing.Point(170, 226);
            this.bntFullScreen.Name = "bntFullScreen";
            this.bntFullScreen.Size = new System.Drawing.Size(75, 22);
            this.bntFullScreen.TabIndex = 1;
            this.bntFullScreen.Text = "FullScreen";
            this.bntFullScreen.UseVisualStyleBackColor = true;
            this.bntFullScreen.Click += new System.EventHandler(this.bntFullScreen_Click);
            // 
            // lblPath
            // 
            this.lblPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblPath.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblPath.Location = new System.Drawing.Point(8, 262);
            this.lblPath.Name = "lblPath";
            this.lblPath.Size = new System.Drawing.Size(373, 30);
            this.lblPath.TabIndex = 2;
            this.lblPath.Text = "Select A File";
            this.lblPath.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // bntPickFile
            // 
            this.bntPickFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bntPickFile.AutoEllipsis = true;
            this.bntPickFile.Location = new System.Drawing.Point(383, 262);
            this.bntPickFile.Name = "bntPickFile";
            this.bntPickFile.Size = new System.Drawing.Size(37, 30);
            this.bntPickFile.TabIndex = 1;
            this.bntPickFile.Text = "...";
            this.bntPickFile.UseVisualStyleBackColor = true;
            this.bntPickFile.Click += new System.EventHandler(this.bntPickFile_Click);
            // 
            // Player
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(424, 301);
            this.Controls.Add(this.lblPath);
            this.Controls.Add(this.bntPickFile);
            this.Controls.Add(this.bntFullScreen);
            this.Controls.Add(this.bntStart);
            this.Controls.Add(this.bntStop);
            this.Controls.Add(this.mediaPlayer);
            this.Name = "Player";
            this.Text = "Player";
            ((System.ComponentModel.ISupportInitialize)(this.mediaPlayer)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private AxWMPLib.AxWindowsMediaPlayer mediaPlayer;
        private System.Windows.Forms.Button bntStop;
        private System.Windows.Forms.Button bntStart;
        private System.Windows.Forms.Button bntFullScreen;
        private System.Windows.Forms.Label lblPath;
        private System.Windows.Forms.Button bntPickFile;
    }
}