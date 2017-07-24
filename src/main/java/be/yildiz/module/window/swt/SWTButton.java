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

package be.yildiz.module.window.swt;

import be.yildiz.module.window.WindowButton;
import be.yildiz.module.window.input.MouseLeftClickListener;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Shell;

/**
 * Wrapper class to manipulate a button with SWT library.
 *
 * @author Grégory Van den Borre
 */
public final class SWTButton implements WindowButton {

    // TODO
    /*
     * create a rationalized arch between the game elements and the window elements, the level of abstraction should be sufficient to be able to reuse the different elements in both environement, no
     * matter the implementation. so we should have an abstraction of the shell, and the window engine should use it instead of the gamewindow, incompatible with swt native windows.
     */

    /**
     * The wrapped SWT button.
     */
    private final Button button;

    /**
     * Create a new button.
     *
     * @param shell Shell containing the button.
     */
    //@requires shell not null.
    public SWTButton(final Shell shell) {
        super();
        this.button = new Button(shell, SWT.None);
    }

    @Override
    public void setMouseLeftClickListener(final MouseLeftClickListener l) {
        this.button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseDown(final MouseEvent e) {
                if (e.button == 1) {
                    l.click();
                }
            }
        });

    }

}
