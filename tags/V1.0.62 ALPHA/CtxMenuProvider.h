#ifndef CTXMENUPROVIDER_H
#define CTXMENUPROVIDER_H

class QMenu;

struct ICtxMenuProvider
{
  virtual void createMenu(QMenu& menu) = 0;
};

#endif // CTXMENUPROVIDER_H

