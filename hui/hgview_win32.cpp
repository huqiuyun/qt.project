
bool HGView::winEvent(MSG *message, long *result)
{
    Q_D(HGView);

    return d->mFrameStyle->winEvent( message, result );
}
