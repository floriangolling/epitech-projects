package com.example.redditech

import android.content.Context
import android.content.SharedPreferences
import android.os.SystemClock
import androidx.test.core.app.launchActivity
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.action.ViewActions.click
import androidx.test.espresso.matcher.ViewMatchers.withId
import androidx.test.platform.app.InstrumentationRegistry
import androidx.test.espresso.contrib.DrawerActions
import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.uiautomator.UiDevice
import androidx.test.uiautomator.UiSelector
import com.example.redditech.activity.MainActivity
import com.example.redditech.controllers.AccountSettingsGet
import com.example.redditech.controllers.NetworkManager
import com.example.redditech.controllers.User
import com.example.redditech.oauth.OAuthManager
import org.junit.*

import org.junit.runner.RunWith

import org.junit.runners.MethodSorters

/**
 * Instrumented test, which will execute on an Android device.
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
@RunWith(AndroidJUnit4::class)
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
class MainActivityTests {

    private var token : String? = null

    @Before
    fun setUp(){
        val context = InstrumentationRegistry.getInstrumentation().targetContext
        val p: SharedPreferences = context.getSharedPreferences("MY_APP", Context.MODE_PRIVATE)
        token = p.getString("TOKEN", null)
        p.edit().putString("TOKEN", null).commit()
        OAuthManager.setRefreshToken("1253828622541-UalkwF68GQkxs9aXTyFYpSYDOLvhxQ")
        OAuthManager.getAccessTokenUsingRefresh(OAuthManager.getRefreshToken()!!, NetworkManager.getClient())
        User.getClientInfo()
        AccountSettingsGet.getSettingsInfo()
        launchActivity<MainActivity>()
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
    fun stage1_NavBarTest() {
        SystemClock.sleep(5000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(3000)
        onView(withId(R.id.nav_profile)).perform(click())
        SystemClock.sleep(3000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(3000)
        onView(withId(R.id.nav_home)).perform(click())
        SystemClock.sleep(3000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(3000)
        onView(withId(R.id.nav_settings)).perform(click())
        SystemClock.sleep(3000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(3000)
        onView(withId(R.id.nav_home)).perform(click())
        SystemClock.sleep(3000)
    }

    @Test
    fun stage2_SpinnerTest() {
        SystemClock.sleep(4000)
        val device = UiDevice.getInstance(InstrumentationRegistry.getInstrumentation())
        val selector = UiSelector()
        val best = device.findObject(selector.textMatches("Best"))
        best.waitForExists(10000)
        if (best.exists())
            best.click()
        SystemClock.sleep(4000)
        val hot = device.findObject(selector.textMatches("Hot"))
        hot.waitForExists(10000)
        if (hot.exists())
            hot.click()
        SystemClock.sleep(4000)
        hot.click()
        SystemClock.sleep(2000)
        val new = device.findObject(selector.textMatches("New"))
        new.waitForExists(10000)
        if (new.exists())
            new.click()
        SystemClock.sleep(4000)
    }

    @Test
    fun stage3_SettingsTest() {
        SystemClock.sleep(2000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(3000)
        onView(withId(R.id.nav_settings)).perform(click())
        SystemClock.sleep(3000)

        val device = UiDevice.getInstance(InstrumentationRegistry.getInstrumentation())
        val selector = UiSelector()
        var set = device.findObject(selector.textMatches("Allow people to follow you"))
        set.waitForExists(10000)
        if (set.exists())
            set.click()
        SystemClock.sleep(3000)
        set = device.findObject(selector.textMatches("Unsubscribe from all emails"))
        set.waitForExists(10000)
        if (set.exists())
            set.click()
        SystemClock.sleep(3000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(3000)
        onView(withId(R.id.nav_home)).perform(click())
        SystemClock.sleep(3000)
    }

    @Test
    fun stage4_SearchBarTest() {
        SystemClock.sleep(5000)
        val device = UiDevice.getInstance(InstrumentationRegistry.getInstrumentation())
        val selector = UiSelector()

        onView(withId(R.id.search)).perform(click())
        SystemClock.sleep(2000)
        val searchBar = device.findObject(selector.textMatches("Search for subreddit"))
        searchBar.waitForExists(10000)
        if (searchBar.exists())
            searchBar.text = "animals"
        SystemClock.sleep(2000)
        device.pressEnter()
        SystemClock.sleep(5000)

        val rAnimals = device.findObject(selector.textMatches("r/Animals"))
        rAnimals.waitForExists(10000)
        if (rAnimals.exists())
            rAnimals.click()
        SystemClock.sleep(3000)
        onView(withId(R.id.join_button_sub_fragment)).perform(click())
        SystemClock.sleep(2000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(2000)
        onView(withId(R.id.nav_home)).perform(click())
        SystemClock.sleep(5000)
    }

    @Test
    fun stage5_LogoutTest() {
        SystemClock.sleep(2000)
        onView(withId(R.id.drawer_layout)).perform(DrawerActions.open())
        SystemClock.sleep(2000)
        onView(withId(R.id.logout_button)).perform(click())
    }
}