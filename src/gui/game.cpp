#include "gui/game.h"

using namespace std;

Game::Game(QWidget* parent, GameState gamestate):
        QDialog(parent),
        indicatorframe(new IndicatorFrame(this, not gamestate.white_to_move))
{
        set_window_size();
        set_background_colour(65, 50, 40);
        set_layout(gamestate);

        show();
}

void Game::set_window_size()
{
        int window_size = QGuiApplication::primaryScreen()->availableGeometry().width() / 3.5;
        setMinimumSize(window_size, window_size);
}

void Game::set_background_colour(int r, int g, int b)
{
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(r, g, b));
        setAutoFillBackground(true);
        setPalette(pal);
}

void Game::set_layout(GameState& gamestate)
{
        QHBoxLayout* hboxlayout = new QHBoxLayout(this);

        hboxlayout->setSpacing(0);
        hboxlayout->setContentsMargins(BORDER, BORDER, 0, BORDER);

        hboxlayout->addWidget(new_tableview(new BoardModel(this, gamestate)));
        hboxlayout->addWidget(indicatorframe);

        setLayout(hboxlayout);
}

QTableView* Game::new_tableview(BoardModel* boardmodel)
{
        QTableView* tableview = new QTableView(this);
        tableview->setModel(boardmodel);

        connect(tableview->model(), SIGNAL(player_change()), indicatorframe, SLOT(switch_player()));
        connect(tableview, SIGNAL(pressed(QModelIndex)), boardmodel, SLOT(cell_click(QModelIndex)));

        tableview->setShowGrid(false);
        tableview->setFrameShape(QFrame::NoFrame);

        tableview->setItemDelegate(new MyDelegate(this));

        tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->horizontalHeader()->hide();

        tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableview->verticalHeader()->hide();

        return tableview;
}
