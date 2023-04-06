import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '../views/Home.vue'
import Login from '../views/Login'
import Register from '../views/Register'
import ChooseArea from '../views/ChooseArea'
import Callback from '../views/Callback';
import Profile from '../views/Profile';

Vue.use(VueRouter)

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
    {
      path: '/',
      name: 'Login',
      component: Login
    },
    {
      path: '/about',
      name: 'About',
      // route level code-splitting
      // this generates a separate chunk (about.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
    },
    {
      path: '/register',
      name: 'Register',
      component: Register,
    },
    {
      path: '/myarea',
      name: 'Home',
      component: Home,
  
    },
    {
      path: '/create',
      name: 'ChooseArea',
      component: ChooseArea,
  
    },
    {
      path: '/auth/callback/:id',
      name: 'auth',
      component: Callback,
    },
    {
      path: '/profile',
      name: 'Profile',
      component: Profile,
  
    }
  ]
});

export default router
