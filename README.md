# IRCサーバープロジェクト

## 1. 概要
このプロジェクトでは、独自のIRCサーバーを開発します。
実際のIRCクライアントを使用して、サーバーへの接続とテストを行います。
インターネットは、コンピュータ同士が相互にやり取りできる標準プロトコルに基づいています。これを理解することは重要です。

## 2. 一般ルール
1. プログラムはクラッシュせず、異常終了しないようにする。
2. `Makefile` を作成し、ソースコードを適切にコンパイルできるようにする。
   - `Makefile` には以下のルールを含めること：`$(NAME), all, clean, fclean, re`
3. C++ 98 規格に準拠し、`-Wall -Wextra -Werror` を使用する。
4. 可能な限り C++ 標準ライブラリを使用し、C 言語の関数よりも C++ のバージョンを優先する。
5. 外部ライブラリおよび Boost ライブラリの使用は禁止。

## 3. 必須機能
### 3.1 プログラム仕様
- **プログラム名:** `ircserv`
- **提出ファイル:** `Makefile, *.h, *.hpp, *.cpp, *.tpp, *.ipp`（必要に応じて設定ファイルを含む）
- **引数:**
  - `port`（リスニングポート）
  - `password`（接続パスワード）
- **使用可能な C++ 98 標準関数:**
  - `socket, close, setsockopt, getsockname, getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo, bind, connect, listen, accept, htons, htonl, ntohs, ntohl, inet_addr, inet_ntoa, send, recv, signal, sigaction, lseek, fstat, fcntl, poll (または同等のもの)`

### 3.2 サーバーの仕様
1. 複数のクライアントを同時に処理できること。
2. `fork` の使用は禁止。すべての I/O 操作はノンブロッキングで行う。
3. `poll()`（または同等の関数）を 1 回のみ使用し、全ての入出力処理を管理する。
4. TCP/IP（IPv4 または IPv6）を使用してクライアントと通信する。

### 3.3 必要な機能
1. 認証、ニックネーム設定、ユーザー名設定、チャンネル参加。
2. プライベートメッセージの送受信、チャンネルメッセージの転送。
3. オペレーターおよび通常ユーザーの管理。
4. 以下のオペレーター向けコマンドを実装：
   - `KICK`（クライアントの追放）
   - `INVITE`（クライアントの招待）
   - `TOPIC`（チャンネルトピックの変更）
   - `MODE`（チャンネルモードの変更）
     - `i`: 招待のみのチャンネル設定
     - `t`: トピック変更をオペレーターのみに制限
     - `k`: チャンネルキー（パスワード）の設定・解除
     - `o`: チャンネルオペレーター権限の付与・解除
     - `l`: チャンネルのユーザー制限の設定・解除

## 4. MacOS 特別ルール
- MacOS では `write()` の挙動が異なるため、`fcntl()` の使用を許可。
- ただし、使用可能な設定は `fcntl(fd, F_SETFL, O_NONBLOCK);` のみ。

## 5. テスト例
1. すべてのエラーケースや問題（部分的なデータ受信、低帯域幅など）を検証する。
2. 簡単なテストとして `nc` を使用可能：
   ```sh
   $> nc -C 127.0.0.1 6667
   com^Dman^Dd
   $>
   ```
   - `Ctrl+D` を使ってコマンドを部分的に送信し、受信パケットの処理を確認する。

## 6. ボーナス機能
以下の追加機能を実装すると、より本格的な IRC サーバーになります。
1. **ファイル転送機能**
2. **ボット機能**
   - ただし、ボーナス機能が評価されるのは、必須機能が完全に動作している場合のみ。

## 7. 提出と評価
1. **Git リポジトリにプロジェクトを提出する。**
2. **評価対象はリポジトリ内のコードのみ。**
3. **テスト用プログラムを作成し、他の受講生の評価時にも活用できるようにする。**
4. **リファレンスクライアントを使用して評価を行う。**

## 8.参考文献
- [IRC client用プログラム](https://irssi.org/)
- [wiki: ircとは](https://ja.wikipedia.org/wiki/Internet_Relay_Chat)
- [qiita: ircとは](https://qiita.com/takesyhi/items/cfde655f5769286a770a)
- [horse: modern irc](https://modern.ircdocs.horse/)
- [qiita: socket通信](https://qiita.com/Y-Yoshimura1997/items/752d89c1e6240cfab0ce)
- [google: cppのコーディング規則](https://ttsuki.github.io/styleguide/cppguide.ja.html)
- [irc: プロトコルとか](https://qiita.com/gu-chi/items/d14c99f716da6133bce8)
- [IRCV3(IRCの拡張様式についての取り決め,irssiがこれに則ってるらしい): ネゴシエーション](https://ircv3.net/specs/extensions/capability-negotiation.html)
- [IRCV3: ルールとか](https://ircv3.net)
- [IRCV3: multi_prefix](https://ircv3.net/specs/extensions/multi-prefix)
- [iterm: pain](https://atsum.in/mac/iterm-multi-pane-broadcast/)