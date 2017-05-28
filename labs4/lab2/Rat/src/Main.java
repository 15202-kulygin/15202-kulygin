
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.imageio.ImageIO;
import java.awt.Color;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.awt.Graphics;
import java.awt.Point;
import java.io.File;
import java.util.Timer;
import java.util.TimerTask;

public class Main {
    public static void main(String[] args)
    {
        java.awt.EventQueue.invokeLater(new Runnable()
        {
            public void run()
            {
                RatGame game = new RatGame();
                game.StartGame();
            }
        });
    }
}

class RatGame extends JFrame {
    public RatGame()
    {
        setSize(width, height);
        setTitle("Rat");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        FieldPanel mainField = new FieldPanel();
        getContentPane().add(mainField);
        setUnits(mainField);
    }
    public void StartGame()
    {
//        Timer t = new Timer();
//        t.scheduleAtFixedRate(new doEachIteration(),1000,1000);
//        repaint();
        this.setVisible(true);
    }
    private void setUnits(FieldPanel mainField) {

        try{

            mainField.setSize(width,height);
            rat = new UnitPanel(resourcePath+"rat.png",cellWidth,cellHeight);
            mainField.add(rat);
            ratLocation = new Point(BOX_COUNT * cellWidth, BOX_COUNT * cellHeight);
            rat.setLocation(ratLocation);
            for (int i = 0; i < BOX_COUNT; ++i)
            {
                boxes[i] = new UnitPanel(resourcePath+"box.png",cellWidth,cellHeight);
                mainField.add(boxes[i]);
                boxesLocation[i] = new Point(i * cellWidth,i * cellHeight);
                boxes[i].setLocation(boxesLocation[i]);
            }
            setVisible(true);
        }
        catch(Exception e){
            System.out.println("qq");
        }
    }



    private UnitPanel rat;
    private UnitPanel[] boxes = new UnitPanel[BOX_COUNT];

    private Point ratLocation = new Point();
    private Point[] boxesLocation =  new Point[BOX_COUNT];

    private final int width = 600;
    private final int height = 600;
    private int cellWidth = width / 10;
    private int cellHeight = height / 10;

    final private static int BOX_COUNT = 4;

    final private static String resourcePath = "C:/Users/Max/prog/labs4/lab2/Rat/src/";

}

class FieldPanel extends JPanel {
    FieldPanel() {
        super(true);
        setOpaque(true);
        setBackground(Color.LIGHT_GRAY);
        setLayout(null);
    }
}

class UnitPanel extends JPanel {
    UnitPanel(String filename,int sizex, int sizey) throws Exception {
        int scalex = sizex;
        int scaley = sizey;
        if (scalex > scaley) {
            scalex = scaley;
        }
        else {
            scaley = scalex;
        }
        BufferedImage imageOriginal = ImageIO.read(new File(filename));
        image = imageOriginal.getScaledInstance(scalex,scaley,Image.SCALE_DEFAULT);
        setBackground(Color.LIGHT_GRAY);
        setSize(sizex,sizey);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image,2,2,null);
    }

    private Image image;
}

