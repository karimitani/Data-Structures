import javax.swing.*; 
import java.awt.*; 
import java.awt.event.*; 
import java.util.*;

abstract class MapMenu extends JMenuBar {
    public JMenuBar _menu;
    public JMenu _modeMenu;
    
    public void toggleModeMenu(String selectedItem) {
        for (int i = 0; i < _modeMenu.getItemCount(); i++){
            JMenuItem item = _modeMenu.getItem(i);
            if (item.getText() == selectedItem) {item.setSelected(true);}
            else {item.setSelected(false);}
        }
    }
}