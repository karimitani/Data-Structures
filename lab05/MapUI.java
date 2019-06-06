import javax.swing.*; 
import java.io.*; 
import java.applet.*; 
import java.net.*;
import javax.swing.text.*; 
import javax.swing.border.*; 
import javax.swing.colorchooser.*; 
import javax.swing.filechooser.*; 
import javax.accessibility.*; 
import java.awt.*; 
import java.awt.event.*; 
import java.beans.*; 
import java.util.*; 

abstract class MapUI extends JFrame implements ActionListener{
    public int PREFERRED_WIDTH = 680;
    public int PREFERRED_HEIGHT = 600;
    public MapMenu _menu;
    public ZoomPane _zoomPane;
    public MapScene _map;
    public MouseAdapter _listener;
    public int CURRENT_MODE = 5;
    public XmlDataSource _data;
    public String currentFileName = null;
}
