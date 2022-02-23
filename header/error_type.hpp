// https://qiita.com/qiita_kuru/items/2f46da304689b6ca2533
#ifndef Error
#define Error uint32_t
#else
// 成功は０で定義します
#define E_SUCCESS            (0x0000)

// 各種エラーの種別を定義します
// 先頭バイトで種類分けするとエラー種別の追加などで拡張する際に整理しやすくなります
#define E_SYSTEM_ERROR       (0x1000)

#define E_IO_ERROR           (0x2000)
#define E_IO_ERROR_NEW_FILE  (0x2001)
#define E_IO_ERROR_OPEN_FILE (0x2002)

// エラー判定用のマクロは以下のように定義できます
#define E_IS_SUCCESS(err)  ((err) == E_SUCCESS)
#define E_HAS_ERROR(err)   ((err) != E_SUCCESS)
#endif
