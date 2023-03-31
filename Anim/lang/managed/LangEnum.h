
#ifndef TUYA_PLANTS_IVY_LANGENUM_H
#define TUYA_PLANTS_IVY_LANGENUM_H
namespace Lang {
    typedef enum {
        ui_boot_waking_up = 0,                  // region 正在唤醒 Ivy
        // en: Waking Ivy
        // jp: Ivyを目覚めさせています
        // zh: 正在唤醒 Ivy
        // endregion
        ui_boot_connect_to_net = 1,             // region Ivy 正在连接无线网络...
        // en: Ivy is connecting to WiFi...
        // jp: IvyはWifiに接続しています…
        // zh: Ivy 正在连接无线网络...
        // endregion
        ui_boot_connect_succ = 2,               // region Ivy 连接网络成功。
        // en: Ivy got WiFi connection.
        // jp: IvyはWifiに接続しました
        // zh: Ivy 连接网络成功。
        // endregion
        ui_boot_connect_fail = 3,               // region Ivy 连接网络失败。
        // en: Ivy failed to connect to WiFi.
        // jp: IvyはWifiの接続に失敗しました
        // zh: Ivy 连接网络失败。
        // endregion
        ui_boot_activating = 4,                 // region Ivy 正在激活...
        // en: Ivy is activating.
        // jp: Ivyを起動しています…
        // zh: Ivy 正在激活...
        // endregion
        ui_boot_activated = 5,                  // region Ivy 激活成功。
        // en: Ivy is activated.
        // jp: Ivyは起動しました
        // zh: Ivy 激活成功。
        // endregion
        ui_boot_activate_fail = 6,              // region Ivy 激活失败。
        // en: Ivy failed to activate.
        // jp: Ivyの起動に失敗しました
        // zh: Ivy 激活失败。
        // endregion
        ui_boot_tuning_time = 7,                // region Ivy 正在同步时间...
        // en: Ivy is tuning its watch...
        // jp: Ivyは時間を同期しています…
        // zh: Ivy 正在同步时间...
        // endregion
        ui_boot_tune_succ = 8,                  // region Ivy 同步时间成功。
        // en: Ivy synchronized its watch.
        // jp: Ivyは時間の同期に成功しました
        // zh: Ivy 同步时间成功。
        // endregion
        ui_boot_tune_fail = 9,                  // region Ivy 同步时间失败。
        // en: Ivy failed to synchronize its watch.
        // jp: Ivyは時間の同期に失敗しました
        // zh: Ivy 同步时间失败。
        // endregion
        ui_boot_locating = 10,                  // region Ivy 正在获取位置信息...
        // en: Ivy is checking map...
        // jp: Ivyは位置を特定しています…
        // zh: Ivy 正在获取位置信息...
        // endregion
        ui_boot_locate_succ = 11,               // region Ivy 定位成功。
        // en: Ivy found itself in map.
        // jp: Ivyは位置の特定に成功しました
        // zh: Ivy 定位成功。
        // endregion
        ui_boot_locate_fail = 12,               // region Ivy 定位失败。
        // en: Ivy lost itself in map.
        // jp: Ivyは位置の特定に失敗しました
        // zh: Ivy 定位失败。
        // endregion
        ui_boot_physical_check = 13,            // region Ivy 正在自检...
        // en: Ivy is doing a physical examination...
        // jp: Ivyは自分を点検しています…
        // zh: Ivy 正在自检...
        // endregion
        ui_boot_physical_succ = 14,             // region Ivy 自检成功。
        // en: Ivy passed the examination.
        // jp: Ivyは自分の点検に成功しました
        // zh: Ivy 自检成功。
        // endregion
        ui_boot_physical_fail = 15,             // region Ivy 自检失败。
        // en: Somehow Ivy didn't pass the examination.
        // jp: Ivyは自分の点検に失敗しました
        // zh: Ivy 自检失败。
        // endregion
        ui_boot_plant_check = 16,               // region Ivy 正在检查植物是否存在...
        // en: Ivy is checking its plant...
        // jp: Ivyは植物の存在を確認しています…
        // zh: Ivy 正在检查植物是否存在...
        // endregion
        ui_boot_plant_checked = 17,             // region Ivy 完成了植物检测。
        // en: Ivy completed plant checking.
        // jp: Ivyは植物の存在を確認しました
        // zh: Ivy 完成了植物检测。
        // endregion
        ui_boot_plant_fail = 18,                // region Ivy 没能完成植物检测。
        // en: Ivy failed to complete plant checking.
        // jp: Ivyは植物の存在を確認できませんでした
        // zh: Ivy 没能完成植物检测。
        // endregion
        ui_boot_calibrating = 19,               // region Ivy 正在校准前触按钮。
        // en: Ivy is calibrating its front button.
        // jp: Ivyはフロントボタンの調整を行なっています
        // zh: Ivy 正在校准前触按钮。
        // endregion
        ui_boot_waked_up = 20,                  // region Ivy 醒了。
        // en: Ivy woke up.
        // jp: Ivyが目を覚ましました
        // zh: Ivy 醒了。
        // endregion
        ui_tu_intro_hi = 21,                    // region 你好
        // en: Hi
        // jp: こんにちは
        // zh: 你好
        // endregion
        ui_tu_intro_ivy = 22,                   // region 我是 Ivy
        // en: I'm Ivy
        // jp: 僕 Ivy
        // zh: 我是 Ivy
        // endregion
        ui_tu_intro_meet = 23,                  // region 很高兴见到你
        // en: Nice to meet you
        // jp: お会いできてうれしいよ
        // zh: 很高兴见到你
        // endregion
        ui_tu_intro_before_enter = 24,          // region 在我们进入教程之前
        // en: Before we enter tutorial
        // jp: 説明に入る前に
        // zh: 在我们进入教程之前
        // endregion
        ui_tu_intro_ready = 25,                 // region 请确保植物已经准备好
        // en: Please make sure the plant is ready
        // jp: 植物の準備ができていることを確認してください
        // zh: 请确保植物已经准备好
        // endregion
        ui_tu_intro_shutdown = 26,              // region #否则#，请长按尾部按键关机
        // en: #Otherwise#, please shutdown by long pressing the back button
        // jp: #でなければ#後ろのボタンを長押しして電源を切ってください
        // zh: #否则#，请长按尾部按键关机
        // endregion
        ui_tu_touch_bar_interact = 27,          // region 使用两侧触摸条交互
        // en: Interact using the two touch bars
        // jp: 左右のタッチバーを使って操作します
        // zh: 使用两侧触摸条交互
        // endregion
        ui_tu_touch_bar_two = 28,               // region Ivy 有两个触摸条
        // en: Ivy has two touch bars
        // jp: 左右にタッチバーがあります
        // zh: Ivy 有两个触摸条
        // endregion
        ui_tu_touch_bar_yellow_dot = 29,        // region #黄色#圆点代表可交互触摸条
        // en: #Yellow# dots imply interactive bars
        // jp: #黄色の#点は相互作用のバーです
        // zh: #黄色#圆点代表可交互触摸条
        // endregion
        ui_tu_touch_bar_left = 30,              // region 现在，尝试触摸左侧触摸条
        // en: Now, let's try touch the left bar
        // jp: それでは左のタッチバーに触れてみてください
        // zh: 现在，尝试触摸左侧触摸条
        // endregion
        ui_tu_touch_bar_right = 31,             // region 很好，触摸右侧触摸条
        // en: Good, now try the right bar
        // jp: いいですね、では右のタッチバーに触れてみてください
        // zh: 很好，触摸右侧触摸条
        // endregion
        ui_tu_touch_bar_great = 32,             // region 太棒了！
        // en: Great!
        // jp: 素晴らしいですね
        // zh: 太棒了！
        // endregion
        ui_tu_water_prepare_plant = 33,         // region 很好，现在我们来准备植物
        // en: Nice! Let's now prepare for the plant
        // jp: では植物の準備をしましょう
        // zh: 很好，现在我们来准备植物
        // endregion
        ui_tu_water_remove_pot = 34,            // region 加水之前请移出花托
        // en: Remove the pot before adding water
        // jp: 水を加える前にポットを取ります
        // zh: 加水之前请移出花托
        // endregion
        ui_tu_water_right_next = 35,            // region 右触执行下一步
        // en: Touch right to the next step
        // jp: 右のタッチバーで次へ進みます
        // zh: 右触执行下一步
        // endregion
        ui_tu_water_assist_good = 37,           // region 很好！
        // en: Good!
        // jp: グッド
        // zh: 很好！
        // endregion
        ui_tu_plant_put_pot = 38,               // region 现在，放入花托
        // en: Now put the inner-pot in
        // jp: ポットを入れます
        // zh: 现在，放入花托
        // endregion
        ui_tu_plant_select_app = 39,            // region 请在#APP#选择你的植物
        // en: Please select your plant in #App#
        // jp: #APP#で植物を選んでください
        // zh: 请在#APP#选择你的植物
        // endregion
        ui_tu_plant_select_switch = 40,         // region 植物选择好后， 此页面会自动切换。
        // en: After the plant is selected, this page will be automatically switched.
        // jp: 植物を選択すると、 ページが自働的に切り替わります
        // zh: 植物选择好后， 此页面会自动切换。
        // endregion
        ui_tu_plant_right_skip = 41,            // region 或者，右触跳过
        // en: Or touch right to skip
        // jp: または右のタッチバーでスキップします
        // zh: 或者，右触跳过
        // endregion
        ui_tu_congratulations = 42,             // region 恭喜！
        // en: Congratulations!
        // jp: おめでとうございます!
        // zh: 恭喜！
        // endregion
        ui_tu_completed = 43,                   // region 你已经完成了所有指导教程！
        // en: You have completed the tutorial!
        // jp: あなたは全てのチュートリアルを終えました!
        // zh: 你已经完成了所有指导教程！
        // endregion
        ui_tu_water_calibrating = 44,           // region 正在校准水位传感器
        // en: Calibrating Level Sensor
        // jp: 水平センサーを補正しています
        // zh: 正在校准水位传感器
        // endregion
        ui_tu_water_prepare_sensor = 45,        // region 正在准备传感器环境...
        // en: Preparing sensor environment...
        // jp: センサー環境を準備しています…
        // zh: 正在准备传感器环境...
        // endregion
        ui_tu_water_wait_moment = 46,           // region 请稍等片刻。
        // en: Please wait for a moment.
        // jp: 少々お待ちください
        // zh: 请稍等片刻。
        // endregion
        ui_tu_water_detected = 47,              // region 检测到有水存在。
        // en: Detected water presence.
        // jp: 水を検知しました
        // zh: 检测到有水存在。
        // endregion
        ui_tu_water_tank_empty = 48,            // region 请确保水仓是空的。
        // en: Please make sure the tank is empty.
        // jp: タンクが空であることを確認してください
        // zh: 请确保水仓是空的。
        // endregion
        ui_tu_water_add_20_water = 49,          // region 请加 20mL 水。
        // en: Please add 20mL of water.
        // jp: 水を20mL入れて下さい
        // zh: 请加 20mL 水。
        // endregion
        ui_tu_water_continue = 50,              // region 加水后 请右触继续。
        // en: After the water is added please touch the right pad to continue.
        // jp: 水を加えたら 右のタッチバーに触れてください
        // zh: 加水后 请右触继续。
        // endregion
        ui_tu_water_calib_completed = 51,       // region 校准完成！
        // en: Calibration completed!
        // jp: 補正終了!
        // zh: 校准完成！
        // endregion
        ui_tu_water_pour_out = 52,              // region 现在，你可以倒出多余的水
        // en: You can now pour out the excess water
        // jp: 余分な水を出すことができます
        // zh: 现在，你可以倒出多余的水
        // endregion
        ui_tu_water_analyzing = 53,             // region 分析中...
        // en: Analyzing...
        // jp: 分析中です…
        // zh: 分析中...
        // endregion
        ui_tu_water_another_20_water = 55,      // region 现在，再加入 20mL 水 (共 {} mL)。
        // en: Now add another 20mL of water ({} mL in total).
        // jp: 水 を20mL追加してください({} mL全体).
        // zh: 现在，再加入 20mL 水 (共 {} mL)。
        // endregion
        ui_tu_water_make_sure = 57,             // region 请确认水已加入。
        // en: Please make sure the water is added.
        // jp: 水が入っていることを確認してください
        // zh: 请确认水已加入。
        // endregion
        ui_actionbox_touch_left = 58,           // region 左触
        // en: touch left
        // jp: 左
        // zh: 左触
        // endregion
        ui_actionbox_touch_right = 59,          // region 右触
        // en: touch right
        // jp: 右
        // zh: 右触
        // endregion
        ui_fluid_select_plant = 60,             // region 请选择你的植物 ( 在 APP 中)
        // en: Please choose your plant ( in APP )
        // jp: 植物 を選択します(アプリで)
        // zh: 请选择你的植物 ( 在 APP 中)
        // endregion
        ui_fluid_analy_ten_mins = 61,           // region 分析中... 大约10分钟完成。
        // en: Analyzing... It takes about 10min to complete.
        // jp: 分析中です… は約10分かかります
        // zh: 分析中... 大约10分钟完成。
        // endregion
        ui_fluid_analy_put_plant = 62,          // region 分析中... 请放入植物继续。
        // en: Analyzing... Please put in plant to continue.
        // jp: 分析中です… 植物を入れてください
        // zh: 分析中... 请放入植物继续。
        // endregion
        ui_fluid_healthy = 63,                  // region 水量适宜。
        // en: Healthy water level.
        // jp: 適切な水位です
        // zh: 水量适宜。
        // endregion
        ui_fluid_absorbing = 64,                // region Ivy 仍在从土壤中吸收水分。
        // en: Ivy is still absorbing water from its soil.
        // jp: Ivyは土から水を吸っています
        // zh: Ivy 仍在从土壤中吸收水分。
        // endregion
        ui_fluid_add_about = 65,                // region 请加水大约 {} mL。
        // en: Please add water to about {} mL.
        // jp: 約{} mLの水を加えてください
        // zh: 请加水大约 {} mL。
        // endregion
        ui_fluid_not_yet = 66,                  // region 不足
        // en: Not Yet
        // jp: まだ
        // zh: 不足
        // endregion
        ui_fluid_too_much = 67,                 // region 过多
        // en: Too Much
        // jp: 多すぎ
        // zh: 过多
        // endregion
        ui_fluid_good = 68,                     // region 适宜
        // en: Good
        // jp: グッド
        // zh: 适宜
        // endregion
        ui_plant_status_illumination_value = 69,// region 光照
        // en: light
        // jp: 光
        // zh: 光照
        // endregion
        ui_plant_status_temperature_value = 70, // region 温度
        // en: temp
        // jp: 温度
        // zh: 温度
        // endregion
        ui_plant_status_ambient_humidity_value = 71,// region 湿度
        // en: humidity
        // jp: 湿度
        // zh: 湿度
        // endregion
        ui_plant_status_soil_humidity_value = 72,// region 土壤
        // en: soil
        // jp: 土壌
        // zh: 土壤
        // endregion
        ui_plant_status_water_level_value = 73, // region 水位
        // en: water
        // jp: 水位
        // zh: 水位
        // endregion
        ui_plant_status_battery_value = 74,     // region 电池
        // en: battery
        // jp: バッテリー
        // zh: 电池
        // endregion
        ui_plant_status_leave = 75,             // region Ivy 暂时离开了。
        // en: Ivy left for the moment.
        // jp: 植物が設置されていません
        // zh: Ivy 暂时离开了。
        // endregion
        ui_plant_status_sun_too_much = 76,      // region 现在光照有点太强了。
        // en: The sunlight is a little too much right now.
        // jp: 日差しが強すぎます
        // zh: 现在光照有点太强了。
        // endregion
        ui_plant_status_sun_not_enough = 77,    // region 光照不足，请把Ivy放到一个更明亮的地方。
        // en: The sunlight is not enough, please put Ivy to a brighter place.
        // jp: 日光が足りません。Ivyをもっと明るい場所に置いてください
        // zh: 光照不足，请把Ivy放到一个更明亮的地方。
        // endregion
        ui_plant_status_sun_good = 78,          // region 光照恰到好处。
        // en: The sunlight is good for Ivy.
        // jp: ちょうどいい陽射し
        // zh: 光照恰到好处。
        // endregion
        ui_plant_status_sun_absorbing = 79,     // region Ivy 明天将继续吸收阳光。
        // en: Ivy will start absorbing light again tomorrow.
        // jp: Ivyは明日も太陽の光を浴びます
        // zh: Ivy 明天将继续吸收阳光。
        // endregion
        ui_plant_status_temp_too_high = 80,     // region 温度太高了。
        // en: The temperature is too high.
        // jp: 温度が高すぎます
        // zh: 温度太高了。
        // endregion
        ui_plant_status_temp_too_low = 81,      // region 温度太低了。
        // en: The temperature is too low.
        // jp: 温度が低すぎます
        // zh: 温度太低了。
        // endregion
        ui_plant_status_temp_good = 82,         // region 温度恰到好处。
        // en: The temperature is good for Ivy.
        // jp: ちょうどいい温度
        // zh: 温度恰到好处。
        // endregion
        ui_plant_status_hum_too_low = 83,       // region 环境湿度太低。
        // en: Air humidity is too low.
        // jp: 湿度が低すぎます
        // zh: 环境湿度太低。
        // endregion
        ui_plant_status_hum_good = 84,          // region 环境湿度恰到好处。
        // en: Air humidity is good for Ivy.
        // jp: ちょうどいい湿度
        // zh: 环境湿度恰到好处。
        // endregion
        ui_plant_status_soil_uncalibrated = 85, // region 传感器需要分析植物土壤环境（在水加足后开始，共约8小时）
        // en: The sensor needs to study the plant-soil environment (starts after adding enough water; takes about 8 hours).
        // jp: センサーは植物の土壌環境を分析する必要があります(十分な水を入れてから約8時間必要です)
        // zh: 传感器需要分析植物土壤环境（在水加足后开始，共约8小时）
        // endregion
        ui_plant_status_soil_unstable = 86,     // region 传感器数值仍在稳定中， 请稍等片刻...
        // en: The sensor value is still stabilizing. This may take a while...
        // jp: センサー数値は安定しています。少々お待ちください…
        // zh: 传感器数值仍在稳定中， 请稍等片刻...
        // endregion
        ui_plant_status_soil_too_low = 87,      // region 土壤有点干。
        // en: The soil is probably a little dry.
        // jp: 土が少し乾いているようです
        // zh: 土壤有点干。
        // endregion
        ui_plant_status_soil_good = 88,         // region 土壤湿度恰到好处。
        // en: The soil moisture is good for Ivy.
        // jp: 土はちょうどいい湿り気
        // zh: 土壤湿度恰到好处。
        // endregion
        ui_plant_status_analyze_has_pot = 89,   // region Ivy 仍在分析中...
        // en: Ivy is still analyzing...
        // jp: Ivyはまだ分析中です…
        // zh: Ivy 仍在分析中...
        // endregion
        ui_plant_status_analyze_not_pot = 90,   // region 分析中...请放入植物继续。
        // en: Analyzing...Please put in plant to continue.
        // jp: 分析中です… 植物を入れてください
        // zh: 分析中...请放入植物继续。
        // endregion
        ui_plant_status_water_good = 91,        // region 水量恰到好处。
        // en: The water level is good for Ivy.
        // jp: ちょうどいい水位
        // zh: 水量恰到好处。
        // endregion
        ui_plant_status_tank_dry_no_need = 92,  // region Ivy 正在从土壤中吸水。
        // en: Ivy is still absorbing water from the soil.
        // jp: Ivyは土から水を吸っています
        // zh: Ivy 正在从土壤中吸水。
        // endregion
        ui_plant_status_tank_dry_simple_need = 93,// region Ivy 有点口渴，请在水仓中加水。
        // en: Ivy is a little thirsty, please add some water to the tank.
        // jp: Ivyは喉が渇いています。水を入れてください
        // zh: Ivy 有点口渴，请在水仓中加水。
        // endregion
        ui_plant_status_tank_dry_strong_need = 94,// region Ivy 非常渴，请立即加水！
        // en: Ivy is very thirsty, please add some water right now!
        // jp: Ivyはとても喉が渇いています。すぐに水を入れてください!
        // zh: Ivy 非常渴，请立即加水！
        // endregion
        ui_plant_status_water_analyzing = 95,   // region 分析中...
        // en: Analyzing...
        // jp: 分析中です…
        // zh: 分析中...
        // endregion
        ui_plant_status_batt_charging = 96,     // region 充电中...
        // en: Charging...
        // jp: 充電中です…
        // zh: 充电中...
        // endregion
        ui_plant_status_batt_undetermined = 97, // region 分析电池状态中，请稍等片刻...
        // en: Analyzing battery status. Please wait for a moment...
        // jp: バッテリーの状態を分析します。少々お待ちください…
        // zh: 分析电池状态中，请稍等片刻...
        // endregion
        ui_plant_status_batt_dry = 98,          // region 电量即将耗尽，请立即为 Ivy 充电！
        // en: Battery is almost run out. Please charge Ivy now!
        // jp: バッテリーが切れます。今すぐIvyを充電してください!
        // zh: 电量即将耗尽，请立即为 Ivy 充电！
        // endregion
        ui_plant_status_batt_low = 99,          // region 电量低！请及时为 Ivy 充电。
        // en: Battery is low! Please charge Ivy in time.
        // jp: バッテリーが少ないです!Ivyを充電してください
        // zh: 电量低！请及时为 Ivy 充电。
        // endregion
        ui_plant_status_batt_good = 100,        // region 电量充足。
        // en: Battery is good.
        // jp: バッテリーは十分です
        // zh: 电量充足。
        // endregion
        ui_prov_tip_title = 101,                // region 配网提示
        // en: ProvisionTip
        // jp: 配信のヒント
        // zh: 配网提示
        // endregion
        ui_xm_prov_tip_general = 102,           // region 1.请打开米家APP. 2.点击 + 号，添加设备. 3.选择智能萌宠花盆Ivy. 4.选择WiFi,输入WiFi密码. 5.点击连接,连接设备.
        // en: 1.Open Mijia App. 2.Click top corner + add equipment. 3.Select smart pet Ivy. 4.Select Wifi and input password. 5.Click OK connect to equipment.
        // jp: 1.Mijia Appを開きます。 2.上部の角をクリックして、+ デバイスを追加をクリックします。 3.smart pet Ivyを選択します。 4.Wifiを選択して、Wifiのパスワードを入力します。 5.接続をクリックしてデバイスを接続します
        // zh: 1.请打开米家APP. 2.点击 + 号，添加设备. 3.选择智能萌宠花盆Ivy. 4.选择WiFi,输入WiFi密码. 5.点击连接,连接设备.
        // endregion
        ui_xm_prov_tip_phone_connected = 103,   // region 手机连接成功!
        // en: The mobile phone connected!
        // jp: 携帯電話に接続しました!
        // zh: 手机连接成功!
        // endregion
        ui_xm_prov_tip_config_router = 104,     // region 配置无线路由信息!
        // en: Config wifi router!
        // jp: Wifiルーターを設定します!
        // zh: 配置无线路由信息!
        // endregion
        ui_xm_prov_tip_complete = 105,          // region 配网完成！等待重启！
        // en: Complete! Waiting for reboot!
        // jp: 完了! 再起動を待っています!
        // zh: 配网完成！等待重启！
        // endregion
        ui_sysinfo_wifi_name = 106,             // region 无线名称
        // en: SSID
        // jp: SSID
        // zh: 无线名称
        // endregion
        ui_sysinfo_public_ip = 107,             // region 公共IP
        // en: Public IP
        // jp: パブリックIP
        // zh: 公共IP
        // endregion
        ui_sysinfo_local_ip = 108,              // region 本地IP
        // en: Local IP
        // jp: ローカルIP
        // zh: 本地IP
        // endregion
        ui_sysinfo_ota_ver = 109,               // region 固件版本
        // en: OTA ver.
        // jp: ファームウェアのバージョン
        // zh: 固件版本
        // endregion
        ui_sysinfo_evolve = 110,                // region 进化
        // en: Evolve
        // jp: アップデート
        // zh: 进化
        // endregion
        ui_sysinfo_location = 111,              // region 位置
        // en: Location
        // jp: 場所
        // zh: 位置
        // endregion
        ui_evolve_check_update_title = 112,     // region 检查更新中
        // en: Checking Updates
        // jp: アップデートを確認中…
        // zh: 检查更新中
        // endregion
        ui_evolve_check_update_desc = 113,      // region 正在从 plantsIO 云端获取最新数据
        // en: requesting from plantsIO server
        // jp: plantsIOサーバーから最新データを取得中…
        // zh: 正在从 plantsIO 云端获取最新数据
        // endregion
        ui_evolve_title = 114,                  // region 进化
        // en: Evolve
        // jp: アップデート
        // zh: 进化
        // endregion
        ui_evolve_desc = 115,                   // region Ivy已经准备好进化, 您想要马上更新吗?
        // en: Ivy is able to evolve, do you want to update now?
        // jp: Ivyはアップデートの準備ができました。今すぐアップデートしますか?
        // zh: Ivy已经准备好进化, 您想要马上更新吗?
        // endregion
        ui_evolve_evolving = 116,               // region 进化中
        // en: Evolving
        // jp: アップデート中…
        // zh: 进化中
        // endregion
        ui_evolve_initializing = 117,           // region 正在初始化
        // en: initializing
        // jp: 初期化しています…
        // zh: 正在初始化
        // endregion
        ui_evolve_total = 118,                  // region 全部
        // en: total
        // jp: すべて
        // zh: 全部
        // endregion
        ui_evolve_not_shutdown = 119,           // region 请不要关闭Ivy
        // en: Please do not shutdown Ivy
        // jp: Ivyの電源を切らないでください
        // zh: 请不要关闭Ivy
        // endregion
        ui_evolve_expressions_files = 120,      // region 新的表情文件
        // en: new expressions
        // jp: 新しい表情ファイル
        // zh: 新的表情文件
        // endregion
        ui_evolve_behavior_tree_files = 121,    // region 行为树文件
        // en: behavior tree files
        // jp: 行動ツリーファイル
        // zh: 行为树文件
        // endregion
        ui_evolve_configuration_files = 122,    // region 配置文件
        // en: configuration files
        // jp: 設定ファイル
        // zh: 配置文件
        // endregion
        ui_evolve_system_files = 123,           // region 系统文件
        // en: system files
        // jp: システムファイル
        // zh: 系统文件
        // endregion
        ui_evolve_downloading = 124,            // region 下载中... 
        // en: downloading
        // jp: ダウンロード中…
        // zh: 下载中... 
        // endregion
        ui_engine_shutdown = 125,               // region 关闭 Ivy
        // en: Shutdown Ivy
        // jp: 電源を切ります
        // zh: 关闭 Ivy
        // endregion
        ui_engine_shutdown_confirm = 126,       // region 你确定要关闭Ivy吗?
        // en: Are you sure you want to shutdown Ivy?
        // jp: Ivyの電源を切りますか?
        // zh: 你确定要关闭Ivy吗?
        // endregion
        ui_engine_reconfig = 127,               // region 重置Ivy
        // en: Reconfig Ivy
        // jp: Ivyを再設定します
        // zh: 重置Ivy
        // endregion
        ui_engine_reconfig_confirm = 128,       // region 您确定要重置Ivy吗?
        // en: Are you sure you want to reconfigure Ivy?
        // jp: Ivyを再設定しますか?
        // zh: 您确定要重置Ivy吗?
        // endregion
        ui_engine_reset = 129,                  // region 重启Ivy
        // en: Reset Ivy
        // jp: Ivyをリセットします
        // zh: 重启Ivy
        // endregion
        ui_engine_reset_confirm = 130,          // region 您确定要重启Ivy并进入工厂测试模式吗?
        // en: Are you sure you want to reset Ivy to factory testing?
        // jp: Ivyをリセットしてテストモードにしますか?
        // zh: 您确定要重启Ivy并进入工厂测试模式吗?
        // endregion
        ui_apply_desc = 131,                    // region 是
        // en: Yes
        // jp: はい
        // zh: 是
        // endregion
        ui_cancel_desc = 132,                   // region 否
        // en: No
        // jp: いいえ
        // zh: 否
        // endregion
        ui_ota_title = 133,                     // region 固件升级
        // en: Upgrade
        // jp: ファームウェアアップデート
        // zh: 固件升级
        // endregion
        ui_ota_remote = 134,                    // region 正在从云端下载...
        // en: Downloading from remote cloud...
        // jp: クラウドからダウンロード中…
        // zh: 正在从云端下载...
        // endregion
        ui_ota_status_downloading = 135,        // region 正在下载...
        // en: Downloading...
        // jp: ダウンロード中…
        // zh: 正在下载...
        // endregion
        ui_ota_status_downloaded = 136,         // region 下载完成.
        // en: Downloaded.
        // jp: ダウンロード完了
        // zh: 下载完成.
        // endregion
        ui_ota_status_installing = 137,         // region 正在安装...
        // en: installing...
        // jp: インストール中…
        // zh: 正在安装...
        // endregion
        ui_ota_status_installed = 138,          // region 安装完成.
        // en: installed.
        // jp: インストール完了
        // zh: 安装完成.
        // endregion
        ui_ota_status_success = 139,            // region 升级成功!
        // en: Upgrade successful!
        // jp: アップグレード成功!
        // zh: 升级成功!
        // endregion
        ui_ota_status_failed = 140,             // region 升级失败.
        // en: Upgrade failed somehow.
        // jp: アップグレードに失敗しました
        // zh: 升级失败.
        // endregion
        ui_ota_status_upgrading = 141,          // region 现在正在升级,可能需要几分钟...
        // en: Upgrading now. It may take a few minutes...
        // jp: 現在アップグレード中です。そのままお待ちください…
        // zh: 现在正在升级,可能需要几分钟...
        // endregion
        ui_tu_prov_config_wifi = 142,           // region 现在，是时候配置无线网络了
        // en: Now it's time to configure WiFi
        // jp: Wifiを設定してください
        // zh: 现在，是时候配置无线网络了
        // endregion
        ui_tu_prov_in_store = 143,              // region 在苹果 / 安卓商店
        // en: In Apple Store / Play Store
        // jp: Apple Store / Google Playにて
        // zh: 在苹果 / 安卓商店
        // endregion
        ui_tu_prov_download = 144,              // region 下载
        // en: download
        // jp: ダウンロード
        // zh: 下载
        // endregion
        ui_tu_prov_ap = 145,                    // region Esp32 SoftAP Provisioning 涂鸦智能
        // en: Esp32 SoftAP Provisioning Tuya Smart
        // jp: Esp32 SoftAP Provisioning Tuya Smart
        // zh: Esp32 SoftAP Provisioning 涂鸦智能
        // endregion
        ui_tu_prov_fail = 146,                  // region 错误的无线网络认证 请重试
        // en: Incorrect WiFi Credentials Please try again
        // jp: Wifi認証が正しくありません もう1度お試しください
        // zh: 错误的无线网络认证 请重试
        // endregion
        ui_tu_tuya_activation = 147,            // region 很好，我们现在来到激活步骤
        // en: Good! Let's now move to activation
        // jp: ではアクティベーションに移りましょう
        // zh: 很好，我们现在来到激活步骤
        // endregion
        ui_tu_open_tuya_app = 148,              // region 打开 #涂鸦智能#
        // en: Open #Tuya Smart#
        // jp: #Tuya Smart#を開きます
        // zh: 打开 #涂鸦智能#
        // endregion
        ui_tu_tuya_add_device = 149,            // region 点击右上角 #添加设备#
        // en: Click #Add Device# at the top right
        // jp: 右上の#デバイスを追加する#をクリックする
        // zh: 点击右上角 #添加设备#
        // endregion
        ui_tu_tuya_scan = 150,                  // region 点击右上角 #扫描按钮#
        // en: Click the #scan icon# at the top right
        // jp: 右上の#スキャンボタン#をクリックします
        // zh: 点击右上角 #扫描按钮#
        // endregion
        ui_tu_touch_right = 151,                // region 右触进行下一步
        // en: Touch right to the next step
        // jp: 右のタッチバーで次へ進みます
        // zh: 右触进行下一步
        // endregion
        ui_tu_loading = 152,                    // region 加载中...
        // en: loading...
        // jp: ロード中…
        // zh: 加载中...
        // endregion
        ui_qr_softap = 153,                     // region 用 #DB0000 ESP32 SoftAP# 扫描配网
        // en: Scan with #DB0000 ESP32 SoftAP# to provision
        // jp: #DB0000 ESP32 software #でスキャンしてください
        // zh: 用 #DB0000 ESP32 SoftAP# 扫描配网
        // endregion
        ui_qr_tuya = 154,                       // region 用 #DB0000 涂鸦智能# 扫描激活
        // en: Scan with #DB0000 Tuya Smart# to activate
        // jp: #DB0000Tuya Smart#でスキャンしてください
        // zh: 用 #DB0000 涂鸦智能# 扫描激活
        // endregion
        ui_tuya_prov_init = 155,                // region 1.打开手机蓝牙. 2.打开涂鸦app. 3.自动发现设备或者点击添加设备. 4.添加萌宠智能花盆Ivy. 5.根据app提示选择wifi,点击连接.
        // en: 1.Please turn on your phone's Bluetooth. 2.Open tuya app. 3.Automatically discover devices or click Add devices. 4.Add Ivy. 5.Select wifi according to the app prompt and click Connect.
        // jp: 1.携帯電話のブルートゥースをオンにしてください. 2.Tuya アプリを開く. 3.デバイスを自動的に検出するか、[デバイスの追加] をクリックします. 4.かわいいペット スマート植木鉢 アイビーを追加. 5.アプリのプロンプトに従って wifi を選択し、[接続] をクリックします.
        // zh: 1.打开手机蓝牙. 2.打开涂鸦app. 3.自动发现设备或者点击添加设备. 4.添加萌宠智能花盆Ivy. 5.根据app提示选择wifi,点击连接.
        // endregion
        ui_tuya_prov_ble_conn = 156,            // region 手机连接设备成功!
        // en: The phone connected to the device successfully!
        // jp: ui_tuya_prov_wifi_conn
        // zh: 手机连接设备成功!
        // endregion
        ui_tuya_prov_wifi_conn = 157,           // region 设备联网成功!
        // en: Device networking success!
        // jp: デバイスネットワーキングの成功!
        // zh: 设备联网成功!
        // endregion
        ui_tuya_prov_activated = 158,           // region 设备激活成功,正在唤醒艾薇......
        // en: The device has activated successfully and is waking up Ivy......
        // jp: デバイスは正常にアクティブ化され、Ivy を起動しています......
        // zh: 设备激活成功,正在唤醒艾薇......
        // endregion
        ui_no_service = 159,                    // region 无服务
        // en: Service Unavailable
        // jp: サービス無し
        // zh: 无服务
        // endregion
        ui_no_service_desc = 160,               // region 当前服务未开启，请在APP中授权相关服务。
        // en: The service is unavailable. Please enable it in the APP.
        // jp: 現在のサービスは有効になっていません。APP で関連するサービスを承認してください。
        // zh: 当前服务未开启，请在APP中授权相关服务。
        // endregion
        ui_tuya_tip_connect_succ = 161,         // region 连网成功
        // en: Connected
        // jp: インターネットに正常に接続されました
        // zh: 连网成功
        // endregion
        ui_tuya_tip_connect_fail = 162,         // region 连网失败
        // en: Lost Connection
        // jp: インターネットに接続できませんでした
        // zh: 连网失败
        // endregion
        ui_tuya_tip_reason_pwd_error = 163,     // region WiFi密码错误
        // en: Incorrect Wi-Fi password
        // jp: 間違った WiFi パスワード
        // zh: WiFi密码错误
        // endregion
        ui_tuya_tip_reason_ap_not_found = 164,  // region 无法连接到指定WiFi
        // en: Unable to connect to Wi-Fi
        // jp: 指定した WiFi に接続できません
        // zh: 无法连接到指定WiFi
        // endregion
        ui_tuya_tip_fail_reset = 165,           // region 请重新检查WiFI状态,重启设备或者重新配网.
        // en: Please check the WiFI status again and restart the device or reconfigure the network.
        // jp: WiFI の状態を再度確認し、デバイスを再起動するか、ネットワークを再構成してください。
        // zh: 请重新检查WiFI状态,重启设备或者重新配网.
        // endregion
        ui_reboot = 166,                        // region 重新启动
        // en: Reboot
        // jp: 再起動
        // zh: 重新启动
        // endregion
        ui_reboot_confirm = 167,                // region 你确定要重启 Ivy 吗？
        // en: Are you sure you want to reboot Ivy?
        // jp: 本当に Ivy を再起動しますか?
        // zh: 你确定要重启 Ivy 吗？
        // endregion
        ui_lang_change = 168,                   // region 语言变更
        // en: Language Change
        // jp: 言語変更
        // zh: 语言变更
        // endregion
        ui_lang_change_desc = 169,              // region 是否立即重启以应用设置？
        // en: Do you want to reboot Ivy now to apply the change?
        // jp: 変更を適用するために Ivy を今すぐ再起動しますか?
        // zh: 是否立即重启以应用设置？
        // endregion
        ui_month = 170,                         // region 月
        // en: ["",[0,"Jan"], [1,"Feb"], [2,"Mar"], [3,"Apr"], [4,"May"], [5,"Jun"], [6,"Jul"], [7,"Aug"], [8,"Sep"], [9,"Oct"], [10,"Nov"], [11,"Dec"]]
        // jp: 月
        // zh: 月
        // endregion
        ui_date = 171,                          // region 日
        // en: Date
        // jp: 日
        // zh: 日
        // endregion
        ui_day = 172,                           // region ["",[0,"星期日"], [1,"星期一"], [2,"星期二"], [3,"星期三"], [4,"星期四"], [5,"星期五"], [6,"星期六"]]
        // en: ["",[0,"SUN"], [1,"MON"], [2,"TUE"], [3,"WED"], [4,"THU"], [5,"FRI"], [6,"SAT"]]
        // jp: ["",[0,"日曜日"],[1,"月曜日"],[2,"火曜日"],[3,"水曜日"],[4,"木曜日"],[5,"金曜日"],[6,"土曜日"]]
        // zh: ["",[0,"星期日"], [1,"星期一"], [2,"星期二"], [3,"星期三"], [4,"星期四"], [5,"星期五"], [6,"星期六"]]
        // endregion
        ui_tuya_tip_reason_week = 173,          // region WiFi信号弱，请靠近路由器
        // en: WiFi signal is weak, please approach the router
        // jp: WiFi 信号が弱いです。ルーターに近づいてください
        // zh: WiFi信号弱，请靠近路由器
        // endregion
        ui_tu_water_no_detected = 174,          // region 未检测到水
        // en: Water not detected
        // jp: 水は検出されませんでした
        // zh: 未检测到水
        // endregion
        ui_tuya_tip_signal_week = 175,          // region 信号弱
        // en: Signal Week
        // jp: シグナルウィーク
        // zh: 信号弱
        // endregion
        ui_prov_popup = 176,                    // region App中 Ivy 将自动出现
        // en: Ivy should popup in APP now
        // jp: Ivy がアプリに自動的に表示されます
        // zh: App中 Ivy 将自动出现
        // endregion
        ui_prov_configuring = 177,              // region 配置中
        // en: Configuring
        // jp: 構成する
        // zh: 配置中
        // endregion
        ui_prov_connecting_router = 178,        // region 连接路由中...
        // en: Connecting to router...
        // jp: ルートに接続しています...
        // zh: 连接路由中...
        // endregion
        ui_prov_router_success = 179,           // region 成功连接路由！
        // en: Connected to router!
        // jp: ルーターが正常に接続されました!
        // zh: 成功连接路由！
        // endregion
        ui_prov_activating = 180,               // region 激活中...
        // en: Activating...
        // jp: 有効化しています...
        // zh: 激活中...
        // endregion
        ui_prov_app_success = 181,              // region APP 已连接！
        // en: App connected!
        // jp: アプリが接続されました！
        // zh: APP 已连接！
        // endregion
        ui_prov_act_success = 182,              // region Ivy 激活成功！
        // en: Successfully activated Ivy!
        // jp: Ivy アクティベーション成功！
        // zh: Ivy 激活成功！
        // endregion
        ui_prov_fail = 183,                     // region 请重新配网并重启 Ivy
        // en: Please restart configuring in APP and reboot Ivy
        // jp: ネットワークを再構成して Ivy を再起動してください
        // zh: 请重新配网并重启 Ivy
        // endregion
        ui_tu_add_app = 184,                    // region 现在添加 Ivy 至 APP
        // en: Now let's add Ivy to APP
        // jp: Ivy を APP に追加しましょう
        // zh: 现在添加 Ivy 至 APP
        // endregion
        ui_tu_download_app = 185,               // region 下载 #涂鸦智能#
        // en: Download #Tuya Smart#
        // jp: #Tuya Smart# をダウンロード
        // zh: 下载 #涂鸦智能#
        // endregion
        ui_in_system_setting = 186,             // region 在手机系统设置中
        // en: In your system setting
        // jp: システム設定で
        // zh: 在手机系统设置中
        // endregion
        ui_enable_ble = 187,                    // region 开启#蓝牙#
        // en: Enable #Bluetooth#
        // jp: #Bluetooth# をオンにする
        // zh: 开启#蓝牙#
        // endregion
        ui_touch_right_config = 188,            // region 右触并开始配置
        // en: Touch right to start configuration
        // jp: 右にタッチして設定を開始
        // zh: 右触并开始配置
        // endregion
    } ui_text_t;
}
#endif //TUYA_PLANTS_IVY_LANGENUM_H
        