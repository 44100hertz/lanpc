static int anim_blink(int left, int length)
{
    return left > (1<<length) || (left & (1<<(left>>(length-3))));
}
