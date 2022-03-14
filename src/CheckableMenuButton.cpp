#include "CheckableMenuButton.h"

CheckableMenuButton::CheckableMenuButton(const QString& label, QWidget* parent) :
    QPushButton(label, parent),
    m_allAction(nullptr)
{
    setMenu(new QMenu(this));
}

void CheckableMenuButton::onAllToggled(const bool checked) {
    for (auto action : menu()->actions())
        if (action != m_allAction && action->isCheckable())
            action->setChecked(checked);
}

void CheckableMenuButton::updateAllChecked() {
    if (!m_allAction)
        return;

    bool all_checked = true;
    for (auto action : menu()->actions()) {
        if (action != m_allAction && action->isCheckable() && !action->isChecked()) {
            all_checked = false;
            break;
        }
    }

    m_allAction->blockSignals(true);
    m_allAction->setChecked(all_checked);
    m_allAction->blockSignals(false);
}

void CheckableMenuButton::setupCheckableAction(QAction* action) {
    action->setCheckable(true);
    action->setChecked(false);
    connect(action, &QAction::triggered, this, &CheckableMenuButton::updateAllChecked);

    if (m_allAction)
        m_allAction->setChecked(false);
}

QAction* CheckableMenuButton::insertCheckableAction(const int index, const QString& text) {
    const auto& actions = menu()->actions();
    if (index == actions.size())
        return addCheckableAction(text);

    auto action = new QAction(text, menu());
    menu()->insertAction(actions[index], action);
    setupCheckableAction(action);

    return action;
}

QAction* CheckableMenuButton::addCheckableAction(const QString& text) {
    auto action = menu()->addAction(text);
    setupCheckableAction(action);

    return action;
}

QAction* CheckableMenuButton::addAllAction(const QString& text) {
    m_allAction = menu()->addAction(text);
    connect(m_allAction, &QAction::toggled, this, &CheckableMenuButton::onAllToggled);
    m_allAction->setCheckable(true);
    updateAllChecked();

    return m_allAction;
}

bool CheckableMenuButton::removeAllAction() {
    if (m_allAction) {
        menu()->removeAction(m_allAction);
        m_allAction = nullptr;
        return true;
    }

    return false;
}

bool CheckableMenuButton::removeAction(const QString& text) {
    for (auto action : menu()->actions())
        if (action != m_allAction && action->text() == text) {
            menu()->removeAction(action);

            if (action->isCheckable())
                updateAllChecked();

            delete action;
            return true;
        }

    return false;
}
