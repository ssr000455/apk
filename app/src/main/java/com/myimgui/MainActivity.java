package com.myimgui;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity {
    private static final int REQUEST_OVERLAY_PERMISSION = 1001;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Button btn = new Button(this);
        btn.setText("启动 ImGui 悬浮窗");
        btn.setOnClickListener(v -> requestOverlayPermission());
        setContentView(btn);
    }

    private void requestOverlayPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (!Settings.canDrawOverlays(this)) {
                Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                        Uri.parse("package:" + getPackageName()));
                startActivityForResult(intent, REQUEST_OVERLAY_PERMISSION);
            } else {
                startNativeActivity();
            }
        } else {
            startNativeActivity();
        }
    }

    private void startNativeActivity() {
        Intent intent = new Intent(this, android.app.NativeActivity.class);
        startActivity(intent);
        Toast.makeText(this, "悬浮窗启动中", Toast.LENGTH_SHORT).show();
        finish();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_OVERLAY_PERMISSION) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                if (Settings.canDrawOverlays(this)) {
                    startNativeActivity();
                } else {
                    Toast.makeText(this, "需要悬浮窗权限", Toast.LENGTH_LONG).show();
                }
            }
        }
    }
}
