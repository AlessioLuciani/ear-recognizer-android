package com.getchlabs.earrecognizer

import android.R.attr
import android.content.Intent
import android.graphics.BitmapFactory
import android.os.Bundle
import android.provider.MediaStore
import android.widget.Button
import android.widget.ImageView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.getchlabs.earrecognizer.recognition.recognize
import org.opencv.android.OpenCVLoader
import java.io.BufferedInputStream
import java.io.InputStream


class MainActivity : AppCompatActivity() {

    val PICK_IMAGE = 1

    private lateinit var btnPickImage: Button
    private lateinit var imgEar: ImageView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        Toast.makeText(this, OpenCVLoader.initDebug().toString(), Toast.LENGTH_LONG).show();

        btnPickImage = findViewById(R.id.btn_pick_image)
        btnPickImage.setOnClickListener { pickImage() }
        imgEar = findViewById(R.id.img_ear)
    }

    fun pickImage() {
        val getIntent = Intent(Intent.ACTION_GET_CONTENT)
        getIntent.type = "image/*"

        val pickIntent = Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI)
        pickIntent.type = "image/*"

        val chooserIntent = Intent.createChooser(getIntent, "Select Image")
        chooserIntent.putExtra(Intent.EXTRA_INITIAL_INTENTS, arrayOf(pickIntent))

        startActivityForResult(chooserIntent, PICK_IMAGE)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == PICK_IMAGE) {
            //TODO: action
            Toast.makeText(this, "Got the image", Toast.LENGTH_SHORT).show()
            val inputStream: InputStream? = getContentResolver().openInputStream(data?.data!!)
            val bufferedInputStream =  BufferedInputStream(inputStream);
            val bmp = BitmapFactory.decodeStream(bufferedInputStream);


            imgEar.setImageBitmap(recognize(bmp, this))

        }
    }
}