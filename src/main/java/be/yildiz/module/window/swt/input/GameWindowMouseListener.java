/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 */

package be.yildiz.module.window.swt.input;

import be.yildiz.common.vector.Point2D;
import be.yildiz.module.window.input.WindowInputListener;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.events.MouseMoveListener;
import org.eclipse.swt.events.MouseWheelListener;
import org.eclipse.swt.widgets.Control;

/**
 * Class for the mouse management. All event are catch here from SWT and then sent to the observer.
 *
 * @author Grégory Van den Borre
 */
public final class GameWindowMouseListener implements MouseListener, MouseMoveListener, MouseWheelListener {

    /**
     * Constant value for mouse left button.
     */
    private static final int LEFT_BUTTON = 1;

    /**
     * Constant value for mouse right button.
     */
    private static final int RIGHT_BUTTON = 3;

    /**
     * Constant value for mouse wheel button.
     */
    private static final int WHEEL_BUTTON = 2;

    /**
     * Last cursor position.
     */
    private final Point2D cursorPosition = new Point2D();

    /**
     * This point is used to compute the difference between the last camera rotation.
     */
    private final Point2D delta = new Point2D();
    /**
     * Event dispatcher.
     */
    private final WindowInputListener dispatcher;
    /**
     * <code>true</code> if the right mouse button is pressed.
     */
    private boolean rightMouse;
    /**
     * <code>true</code> if the left mouse button is pressed.
     */
    private boolean leftMouse;
    /**
     * <code>true</code> if the wheel button is pressed.
     */
    private boolean wheelButton;

    /**
     * Full constructor.
     *
     * @param c          SWT control element, it can be any widget with mouse interaction capability.
     * @param dispatcher Input listener
     */
    public GameWindowMouseListener(final Control c, final WindowInputListener dispatcher) {
        super();
        this.dispatcher = dispatcher;
        c.addMouseMoveListener(this);
        c.addMouseListener(this);
        c.addMouseWheelListener(this);
    }

    /**
     * Notify that mouse button is up.
     *
     * @param e Event retrieved from the listener.
     */
    @Override
    public void mouseUp(final MouseEvent e) {

        if (e.button == GameWindowMouseListener.LEFT_BUTTON) {
            this.dispatcher.mouseLeftReleased(this.cursorPosition);
            this.leftMouse = false;
        } else if (e.button == GameWindowMouseListener.RIGHT_BUTTON) {
            this.dispatcher.mouseRightReleased(this.cursorPosition);
            this.rightMouse = false;
        } else if (e.button == GameWindowMouseListener.WHEEL_BUTTON) {
            this.wheelButton = false;
        }
        this.delta.setValues(0, 0);
    }

    /**
     * Mouse button press actions: If the left button is pressed: camera ray selection is called. If the right button is pressed, the camera will rotate or make an action for a unit.
     *
     * @param event Event retrieved from the listener.
     */
    @Override
    public void mouseDown(final MouseEvent event) {
        switch (event.button) {
            case GameWindowMouseListener.LEFT_BUTTON:
                this.leftMouse = true;
                this.dispatcher.mouseLeftClick(this.cursorPosition.getX(), this.cursorPosition.getY());
                break;
            case GameWindowMouseListener.RIGHT_BUTTON:
                this.rightMouse = true;
                this.dispatcher.mouseRightClick(this.cursorPosition);
                break;
            case GameWindowMouseListener.WHEEL_BUTTON:
                this.wheelButton = true;
                break;
            default:
                break;
        }
    }

    @Override
    public void mouseDoubleClick(final MouseEvent event) {
        if (event.button == GameWindowMouseListener.LEFT_BUTTON) {
            this.dispatcher.mouseDoubleClick(this.cursorPosition);
        }
    }

    /**
     * Moving mouse actions: check if a button is pressed or not and call appropriate logic.
     *
     * @param event Event retrieved from the listener.
     */
    @Override
    public void mouseMove(final MouseEvent event) {
        this.delta.setX(this.cursorPosition.getX() - event.x);
        this.delta.setY(this.cursorPosition.getY() - event.y);
        this.cursorPosition.setValues(event.x, event.y);
        if (this.rightMouse) {
            this.dispatcher.mouseDragRight(this.cursorPosition, this.delta);
        } else if (this.leftMouse) {
            this.dispatcher.mouseDragLeft(this.cursorPosition, this.delta);
        } else if (this.wheelButton) {
            this.dispatcher.mouseDragWheel(this.cursorPosition, this.delta);
        } else {
            this.dispatcher.mouseMove(this.cursorPosition);
        }
    }

    @Override
    public void mouseScrolled(final MouseEvent e) {
        this.dispatcher.mouseWheel(this.cursorPosition, e.count);
    }
}
