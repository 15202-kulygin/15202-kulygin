import javax.swing.*;

class Canvas extends JComponent
{
	@Override
	public void paintComponent(Graphics g)
	{
		Graphics2D g2d = (Graphics2D)g;
		g2d.drawLine(0, 0, x, y);
	}
	public void setLineCoords(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	private int x;
	private int y;

}

class MyKeyboardListener extends KeyAdapter
{
	@Override
	public void keyType(KeyEvent event)
	{
		System.out.println(event.getKeyChar());
	}
}


class MyMouseListener extends MouseAdapter
{
	MyMouseListener(Canvas canvas)
	{
		this.canvas = canvas;
	}
	@Override
	public void mouseClicked(MouseEvent e)
	{
		System.out.println(e.getX() + " " + e.getY());
		canvas.setLineCoords(e.getX(), e.getY());
		canvas.repaint();

	}

	private Canvas canvas;
}

class SwingRunner implements Runnable{
    @Override
    public void run()
    {
        JFrame frame = new JFrame();
        frame.addKeyListener(new MyKeyboardListener());
        Canvas canvas = new Canvas();

        frame.add(canvas);
        canvas.addMouseListener(new MyMouseListener(canvas));


        frame.setMinimumSize(new Dimension(500, 500));
        frame.setVisible(true);
    }
}

public class Main
{
    public static void main (String [] args)
	{
        System.out.println("Main Thread " + Thread.currentThread().getId());
        SwingUtilities.invokeLater(new SwingRunner());

	}
}