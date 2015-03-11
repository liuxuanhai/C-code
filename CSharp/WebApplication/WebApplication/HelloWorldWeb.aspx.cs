using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class HelloWorldWeb : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        this.Title = "Hello World Web";
        
        Label lblShow = new Label();
        lblShow.Text = "Hello, C# Wrold!";

        this.Controls.Add(lblShow);
    }
}