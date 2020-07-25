#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include <QSlider>

class Volume : public QWidget
{
    Q_OBJECT
public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();

    void setValue(int value);

signals:
    void signalVolumeChanged(int volume);

private:
    void initUI();
    void onVolumeChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent *e) override;

private:
    QSlider* m_slider;
};

#endif // VOLUME_H
