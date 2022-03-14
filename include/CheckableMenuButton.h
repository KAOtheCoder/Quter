#ifndef CHECKABLEMENUBUTTON_H
#define CHECKABLEMENUBUTTON_H

#include "Quter.h"

#include <QPushButton>
#include <QMenu>

class QUTER_EXPORT CheckableMenuButton : public QPushButton
{
public:
    CheckableMenuButton(const QString& label, QWidget* parent = nullptr);

    QAction* addCheckableAction(const QString& text);

    template <typename Func2>
    QAction* addCheckableAction(const QString& text, Func2 functor) {
        auto action = addCheckableAction(text);
        connect(action, &QAction::toggled, functor);
        return action;
    }

    template <typename Func2>
    QAction* addCheckableAction(const QString& text, const typename QtPrivate::FunctionPointer<Func2>::Object* context, Func2 functor) {
        auto action = addCheckableAction(text);
        connect(action, &QAction::toggled, context, functor);
        return action;
    }

    QAction* insertCheckableAction(const int index, const QString& text);

    template <typename Func2>
    QAction* insertCheckableAction(const int index,
        const QString& text,
        const typename QtPrivate::FunctionPointer<Func2>::Object* context,
        Func2 functor)
    {
        auto action = insertCheckableAction(index, text);
        connect(action, &QAction::toggled, context, functor);
        return action;
    }

    template <typename Func2>
    QAction* insertCheckableActionSorted(const QString& text,
        const typename QtPrivate::FunctionPointer<Func2>::Object* context,
        Func2 functor,
        const Qt::CaseSensitivity cs = Qt::CaseSensitive)
    {
        const auto& actions = menu()->actions();
        const int actions_size = actions.size();
        for (int i = 0; i < actions_size; ++i)
            if (actions[i] != m_allAction && !actions[i]->isSeparator() && text.compare(actions[i]->text(), cs) < 0)
                return insertCheckableAction(i, text, context, functor);

        return addCheckableAction(text, context, functor);
    }

    QAction* allAction() const { return m_allAction; }
    QAction* addAllAction(const QString& text = "All");
    bool removeAllAction();

    bool removeAction(const QString& text);

private:
    void setupCheckableAction(QAction* action);
    void onAllToggled(const bool checked);
    void updateAllChecked();

    QAction* m_allAction;
};

#endif // CHECKABLEMENUBUTTON_H
