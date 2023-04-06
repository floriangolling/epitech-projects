package com.example.redditech

import android.content.Context
import android.content.SharedPreferences
import android.os.SystemClock
import androidx.test.core.app.launchActivity
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.action.ViewActions.click
import androidx.test.platform.app.InstrumentationRegistry
import androidx.test.espresso.matcher.ViewMatchers.*
import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.uiautomator.UiDevice
import androidx.test.uiautomator.UiSelector
import com.example.redditech.activity.LoginActivity
import com.example.redditech.oauth.OAuthManager
import org.junit.*

import org.junit.runner.RunWith

import org.junit.runners.MethodSorters

@RunWith(AndroidJUnit4::class)
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
class LoginActivityTests {

    private var token: String? = null

    @Before
    fun setUp() {
        val context = InstrumentationRegistry.getInstrumentation().targetContext
        val p: SharedPreferences = context.getSharedPreferences("MY_APP", Context.MODE_PRIVATE)
        OAuthManager.setRefreshToken("")
        token = p.getString("TOKEN", null)
        p.edit().putString("TOKEN", null).commit()
        launchActivity<LoginActivity>()
    }

    @After
    fun cleanEverything() {
        OAuthManager.setRefreshToken("")
        OAuthManager.setAccessToken("")
        val context = InstrumentationRegistry.getInstrumentation().targetContext
        val p: SharedPreferences = context.getSharedPreferences("MY_APP", Context.MODE_PRIVATE)
        p.edit().putString("TOKEN", token).apply()
    }

    @Test
    fun stage1_OAuthTest() {
        SystemClock.sleep(5000)
        onView(withId(R.id.button)).perform(click())
        val device = UiDevice.getInstance(InstrumentationRegistry.getInstrumentation())
        val selector = UiSelector()

        var chromeAccept = device.findObject(selector.textMatches("Accept & continue"))
        SystemClock.sleep(2000)
        chromeAccept.waitForExists(10000)
        if (chromeAccept.exists())
            chromeAccept.click()

        chromeAccept = device.findObject(selector.textMatches("No thanks"))
        chromeAccept.waitForExists(10000)
        if (chromeAccept.exists())
            chromeAccept.click()

        chromeAccept = device.findObject(selector.textMatches("No Thanks"))
        chromeAccept.waitForExists(10000)
        if (chromeAccept.exists())
            chromeAccept.click()

        val textInputUsername = device.findObject(selector.resourceId("user_login"))
        val testPasswordUsername = device.findObject(selector.resourceId("passwd_login"))

        textInputUsername.waitForExists(4000)
        testPasswordUsername.waitForExists(4000)

        if (textInputUsername.exists()) {

            textInputUsername.text = "frostbloody2"
            testPasswordUsername.text = "unsupermotdepasse"
            SystemClock.sleep(1500)
            device.pressEnter()
        }

        val savePassword = device.findObject(selector.textMatches("Never"))
        savePassword.waitForExists(10000)
        if (savePassword.exists())
            savePassword.click()


        device.findObject(selector.textMatches("Allow")).click()

        val openWith = device.findObject(selector.textMatches("Redditech"))
        openWith.waitForExists(10000)
        if (openWith.exists())
            openWith.click()

        val justONce = device.findObject(selector.textMatches("JUST ONCE"))
        justONce.waitForExists(10000)
        if (justONce.exists()) {
            SystemClock.sleep(1500)
            justONce.click()
        }
    }
}