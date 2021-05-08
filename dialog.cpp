#include "dialog.h"
#include "ui_dialog.h"
#include "gamestate.h"
#include <iostream>

enum CONSTANTS {
        MARGIN_LEFT = 5,
        MARGIN_TOP = 5,
        MARGIN_RIGHT = 5,
        MARGIN_BOTTOM = 5,
        BOARD_SIZE = 480,
        SQUARE_SIZE = 60
};

using namespace std;

Dialog::Dialog(QWidget *parent):
        QDialog(parent),
        ui(new Ui::Dialog),
        timer(new QTimer(this))
{
        connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        timer->start(20);
        table->setModel(grid);
        setFixedSize(1.2*BOARD_SIZE, 1.2*BOARD_SIZE);

        table->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->addWidget(table);

        table->setItemDelegate(new MyDelegate);

        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->horizontalHeader()->hide();
        table->verticalHeader()->hide();
        table->setFrameShape(QFrame::NoFrame);

        setLayout(layout);

}

Dialog::~Dialog()
{
        delete ui;
}

void Dialog::nextFrame()
{
        update();
}

void Dialog::mouseReleaseEvent(QMouseEvent* event)
{
        if (event->button() != Qt::LeftButton) {
                return;
        }

        int x = (event->x() - 36) / 69;
        int y = 7 - ((event->y() - 36) / 69);

        select_square(x, y);
}

void Dialog::add_circles()
{
        if (m_potential_states.size() != 0) {
                for (auto& state : m_potential_states) {
                        pair<int, int> cell = state->current_move;
                }
        }
}

void Dialog::select_square(int x, int y)
{
        if (x < 0 or x >= 8 or y < 0 or y >= 8) {
                return;
        }

        char p = m_gamestate(x, y);

        if (p > 0 and is_white(p) == m_gamestate.white_to_move) {

                m_potential_states = piecemove::moves(m_gamestate, x, y);

                if (m_potential_states.size() != 0) {
                        m_x = x;
                        m_y = y;
                }
                add_circles();

                return;
        }

        for (auto& state : m_potential_states) {
                if (make_pair(x, y) == state->current_move) {
                        m_gamestate = GameState(*state);
                }
        }

        m_potential_states.clear();
}

bool Dialog::is_white(char p)
{
        return (p == 'p' or p == 'r' or p == 'n' or p == 'b' or p == 'q' or p == 'k');
}
