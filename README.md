## fluentd
arduinoにメッセージを送るのにtagged_udpプラグインを用いる．

`gem install fluent-plugin-tagged_udp`

でプラグインのインストールする．

## Arduinoボードにプログラムを書き込む

[ここ](https://www.arduino.cc/en/main/software)からArduinoIDEをダウンロードしてインストール．

IDEを起動したら，ツールタブのボードを"Arduino Yun Mini"に，シリアルポートを"arduino at 192.168.11.192"に指定．

左上の"マイコンボードに書き込む"アイコンでプログラム書き込み

パスワードを聞かれたら，いつものを入力．

## ArduinoのLinuxにプログラムを書き込む

`ssh root@192.168.11.192`

or

`ssh root@arduino.local`

でログイン．パスワードはいつもの．

プログラムは/mnt下に配置を推奨(root直下でも問題はない)．

## 注意点
linuxでpythonが動いている状態では，bridge.pyの起動に失敗してしまう．つまり，Arduinoボードとのシリアル通信に必要なプログラムが起動しないので，シリアル通信が出来ない．

いつまで経っても上手くLEDが光らなかったら，linuxにログインして

```
ps | grep python
kill プロセス番号
```

でpythonを終了させると，bridge.pyが起動する．
