/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.redexlinemap;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class InlineMainV2 {

  InlineTestCode itc;

  @BeforeClass
  public static void checkTests() throws Exception {
    InlineTestCode.checkTests(InlineMainV2.class);
  }

  @Before
  public void setUp() throws Exception {
    itc =
        new InlineTestCode(
            new LineMapperV2(getClass().getResourceAsStream("/assets/redex-line-number-map-v2")));
  }

  /** Check that the stack trace of a non-inlined function makes sense. */
  @Test
  public void testBasic() throws Exception {
    itc.testBasic();
  }

  /** Check the stack trace of a once-inlined function. */
  @Test
  public void testInlineOnce() throws Exception {
    itc.testInlineOnce();
  }

  /** Check the stack trace of a multiply-inlined function. */
  @Test
  public void testInlineTwice() throws Exception {
    itc.testInlineTwice();
  }

  @Test
  public void testPositionReset() throws Exception {
    itc.testPositionReset();
  }

  @Test
  public void testElseThrows() throws Exception {
    itc.testElseThrows();
  }

  @Test
  public void testElseThrowsOverload() throws Exception {
    itc.testElseThrowsOverload();
  }
}
